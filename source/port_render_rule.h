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

/* Original 0x4b14c0 (eax = actor, edx and ebx = where the drawn width and height go): the size
 * to draw. The source size is the image's (+4 and +8 of the actor's +0xb4, whose byte +0x27 goes to
 * 0x5bb731) or else the actor's own (+0xf4, +0xf8); the image goes to 0x5bb734. The scale in
 * sixteenths is the actor's byte +0x44, or with its byte +0x91 set the screen's (+0x221 of
 * [0x544070], 16 when its +0x220 is set); below or above 16 each size is scaled (the remainder
 * rounded by the table at 0x5c1b00). The drawn sizes (sign-extended from 16 bits) are stored at
 * edx and ebx and in 0x5bb74c and 0x5bb74e; the source sizes in 0x5bb7b4 and 0x5bb7b6 and the
 * scale in 0x5bb738. Returns 1, with edx the source height under the image pointer's high half. */
uint32_t vertrix_port_render_source_size(PORT_SIGNATURE);

/* Original 0x4ae250: prepare the drawing state. When the image's format byte (0x5bc000) is not
 * the target's (0x5bb730), its colour entry (0x54b808) is split into the tint words at 0x54d5dc
 * and its colour (0x54b83c, kept at 0x5bc008) into the bytes at 0x54d5e8, the halved colour at
 * 0x54d5ec and the select byte (0x54b804 by the colour's entry index) at 0x54d5f0. With blending
 * on (0x5bb739), the level tables (0x55f1f0, 0x55f1f4) and shade tables (0x5785f8, 0x5785fc) are
 * the rows of the opacity (0x5bc00e, in percent) and of 100 less it. The channel maps
 * (0x54cdc8) are the rows at 0x54bb90 from the high half of 0x5bc000 (signed); mirrored drawing
 * (0x5bb73a) then calls 0x4754e0 on the byte 0x5bb7b8, plain drawing sets 0x54cdcc to 0x54d1d0.
 * Returns 0x4754e0's eax, or the last value the original computed in eax; edx is unchanged. */
uint32_t vertrix_port_render_prepare(PORT_SIGNATURE);

/* Original 0x48d7f0: paint one pixel through the palette: the source pixel ([[0x5bb764]]) reduced
 * to 6 bits a channel picks a palette index from [0x54b800] (every fourth byte), its entry from
 * [0x54cdc8] (kept at 0x54d5d0) gives the tinted channels at the offsets 0x54d5dc, 0x54d5de and
 * 0x54d5e0, stored at [0x5bb768] as 0x00rrggbb. Returns that; edx is unchanged. */
uint32_t vertrix_port_render_palette_pixel(PORT_SIGNATURE);

/* Original 0x492880 (eax = row routine): call it for each visible row (the word 0x5bb752 counting
 * down, ebx its count, ax the visible width also stored at 0x5bc016), stepping the source
 * (0x5bb764) past the skipped pixels (0x5bb79c dwords) and the target (0x5bb768) by its skip
 * (0x5bb7c8). Returns the target skip (eax unchanged when there are no rows); edx is unchanged. */
uint32_t vertrix_port_render_rows(PORT_SIGNATURE);

/* Originals 0x49a590, 0x4a2650 and 0x4aa350: 0x492880's code with the target pixel at 0x5bb780,
 * 0x5bb780 and 0x5bb778. */
uint32_t vertrix_port_render_rows_49a590(PORT_SIGNATURE);
uint32_t vertrix_port_render_rows_4a2650(PORT_SIGNATURE);
uint32_t vertrix_port_render_rows_4aa350(PORT_SIGNATURE);

/* Original 0x490c60: blend the source pixel ([[0x5bb764]]) into the target ([[0x5bb768]]): each
 * channel is (source weight [0x55f1f0] + target weight [0x55f1f4] + the colour 0x54d5e8 to
 * 0x54d5ea) halved, the halves ORed in place (a carry spills into the channel above). That pixel
 * goes through the palette as 0x48d7f0 does, its entry kept at 0x54d5d4 (red, green and blue
 * offsets in its top three bytes). Returns the target's address; edx is unchanged. */
uint32_t vertrix_port_render_palette_blend(PORT_SIGNATURE);

/* Original 0x4907d0: mix the source pixel into the target through the palette: both pixels' palette
 * indexes (as 0x48d7f0 finds them) pick words from the tables at [0x5785f8] and [0x5785fc], whose
 * sum (a signed word) is the entry in [0x54cdc8] (kept at 0x54d5d0) the colour comes from. Returns
 * the target's address; edx is unchanged. */
uint32_t vertrix_port_render_palette_mix(PORT_SIGNATURE);

/* Original 0x48ea30: add the source pixel to the target, saturating each channel: the source's
 * palette entry (0x54d5d4, from its index as 0x48d7f0 finds it) gives the channels halfway to the
 * tint (0x54d5dc to 0x54d5e0) in its palette (0x54d5d0); the colour is kept at 0x5bc018, the
 * unsaturated sum at 0x54d624. Returns the target's address; edx is unchanged. */
uint32_t vertrix_port_render_palette_add_tinted(PORT_SIGNATURE);

/* Original 0x48ec70: 0x48ea30 subtracting, each channel stopping at 0. */
uint32_t vertrix_port_render_palette_subtract_tinted(PORT_SIGNATURE);

/* Original 0x491620: 0x48ea30 with the entry picked through the selector table [0x54b804] and the
 * entry tables [0x54cdcc] (the index kept at 0x54d5e4) and the channels taken untinted. */
uint32_t vertrix_port_render_palette_add(PORT_SIGNATURE);

/* Original 0x48da80: average a palette pixel: the source's entry (0x54d5d4) and the target's index
 * pick, by their halved sum, a palette (0x54d5d0) the source entry's three channel bytes are mapped
 * through into the target pixel. Returns the target pixel's address; edx is unchanged. */
uint32_t vertrix_port_render_palette_average(PORT_SIGNATURE);

/* Original 0x48dba0: halve a palette pixel: the source's entry (0x54d5d4) picks the palette
 * (0x54d5d0) and each channel of the target pixel is the palette at the halved sum of the source's
 * and the target's (0x54d5d8) entry bytes. Returns the target pixel's address; edx is unchanged. */
uint32_t vertrix_port_render_palette_halve(PORT_SIGNATURE);

/* Original 0x48de30: map a palette pixel: the source's index picks the palette (0x54d5d0) the
 * target's entry (0x54d5d4) bytes are mapped through. Returns the target pixel's address; edx is
 * unchanged. */
uint32_t vertrix_port_render_palette_map(PORT_SIGNATURE);

#endif
