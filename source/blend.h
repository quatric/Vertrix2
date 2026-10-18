#ifndef BLEND_H
#define BLEND_H
#include "port.h"

/* Clean ports of the renderer's per-pixel operations (port.h). Each works on one 32-bit pixel: the
 * source pixel's address is the global 0x5bb764 and the target's 0x5bb768.
 *
 * A remap looks the source colour up in two tables: its top six bits of red, green and blue
 * (bits 18..23, 10..15 and 2..7) index the dwords at [0x54b800], and the low byte of the entry
 * found selects a 256-byte map from the dwords at [0x54cdc8]. The remapped colour is that map
 * applied to the entry's bytes 3, 2 and 1 (red, green, blue). The entry goes to the global
 * 0x54d5d4 and the map's address to 0x54d5d0.
 *
 * The blends keep the colour in its low 24 bits: a saturating add or subtract clears each
 * channel's lowest bit and puts the raw sum in the global 0x54d624; an average halves both
 * colours. Every routine leaves edx unchanged. */

/* Original 0x48d720: the target becomes the source. Returns the colour. */
uint32_t vertrix_port_blend_copy(PORT_SIGNATURE);

/* Original 0x48d740: the target becomes the remapped source. Returns the remapped colour. */
uint32_t vertrix_port_blend_remap(PORT_SIGNATURE);

/* Original 0x48dd00: saturating add of the source to the target. Returns the target address. */
uint32_t vertrix_port_blend_add(PORT_SIGNATURE);

/* Original 0x48dd50: saturating subtract of the source from the target. Returns the target
 * address. */
uint32_t vertrix_port_blend_subtract(PORT_SIGNATURE);

/* Original 0x48dff0: the target becomes the average of source and target, then that average
 * remapped. Returns the target address. */
uint32_t vertrix_port_blend_average_remap(PORT_SIGNATURE);

/* Original 0x48e190: saturating add of the remapped source (also stored at 0x5bc018). Returns the
 * target address. */
uint32_t vertrix_port_blend_remap_add(PORT_SIGNATURE);

/* Original 0x48e280: saturating subtract of the remapped source (also stored at 0x5bc018).
 * Returns the target address. */
uint32_t vertrix_port_blend_remap_subtract(PORT_SIGNATURE);

/* Original 0x48e850: the average of the target and the source remapped through fixed channels
 * (below; stored at 0x5bc018). Returns the target address. */
uint32_t vertrix_port_blend_tint_average(PORT_SIGNATURE);

/* Original 0x48e900: saturating add of the source remapped through fixed channels (stored at
 * 0x5bc018). Only the entry's low byte is used: the map it selects is applied to the 16-bit
 * indexes in the globals 0x54d5dc, 0x54d5de and 0x54d5e0 for red, green and blue. Returns the
 * target address. */
uint32_t vertrix_port_blend_tint_add(PORT_SIGNATURE);

/* Original 0x48d8c0: the target becomes the source remapped half way to fixed channels: the map
 * the entry selects is applied to the mean (rounded down) of each of the entry's bytes 3, 2 and 1
 * and the 16-bit index in 0x54d5dc, 0x54d5de and 0x54d5e0 respectively. Returns the colour. */
uint32_t vertrix_port_blend_half_tint(PORT_SIGNATURE);

/* Original 0x490560: each channel of the target becomes the sum of the source's channel looked up
 * in the byte table at [0x55f1f0] and the target's in the table at [0x55f1f4] (the sums or-ed
 * into place), and then that colour remapped. Returns the target address. */
uint32_t vertrix_port_blend_levels_remap(PORT_SIGNATURE);

/* Original 0x4902a0: the target becomes the two-table sum of 0x490560, not remapped. Returns the
 * target address. */
uint32_t vertrix_port_blend_levels(PORT_SIGNATURE);

/* Original 0x4901a0: the source's colour entry (stored at 0x54d5d4) is remapped through the map
 * whose number is the 16-bit sum of the word for the entry's low byte in the table at [0x5785f8]
 * and the word for the target's own entry byte in the table at [0x5785fc] (signed). The map's
 * address goes to 0x54d5d0 and the target becomes the remapped colour. Returns the target
 * address. */
uint32_t vertrix_port_blend_shade(PORT_SIGNATURE);

/* Original 0x492550: as 0x492280 with a sampled source: after each pixel the source address moves
 * by four times the next byte of the step list at [0x5bb7dc] (the list address is stored after
 * each step). The count is not tested first: a zero count runs 65536 pixels. The pixel operation
 * gets ebx's upper half from the entry and the count below it, and ecx the source address.
 * Returns the step list address after the last step; edx is unchanged. */
uint32_t vertrix_port_render_sampled_row32(PORT_SIGNATURE);

/* Originals 0x49a270 and 0x4a2330: the same for 16-bit targets (the pixel at 0x5bb780, two bytes
 * on). */
uint32_t vertrix_port_render_sampled_row32_49a270(PORT_SIGNATURE);
uint32_t vertrix_port_render_sampled_row32_4a2330(PORT_SIGNATURE);

/* Original 0x492400: run the pixel operation at [0x5bb72c] for each of the 16-bit count at
 * 0x5bc016 pixels, advancing the source and target addresses by four after each. The count is
 * stored before each call and read back after it (as the low 16 bits of edx for the next call,
 * whose upper bits are the last call's edx); the next call has ecx and ebx the advanced source
 * and target addresses and eax the last call's eax. The count left (0) is stored at the end.
 * Returns the last call's eax (eax unchanged without pixels); edx is unchanged. */
uint32_t vertrix_port_render_row32(PORT_SIGNATURE);

/* Originals 0x49a120 and 0x4a21e0: the same for 16-bit targets (the pixel at 0x5bb780, two bytes
 * on). */
uint32_t vertrix_port_render_row32_49a120(PORT_SIGNATURE);
uint32_t vertrix_port_render_row32_4a21e0(PORT_SIGNATURE);

/* Original 0x492280: as 0x492400 for a source with an alpha byte: the pixel operation runs only
 * for the pixels whose top byte is not 0 (eax that byte, edx's low 16 bits the count with the
 * upper bits those of the last target address plus four, ecx the source address). The source
 * address and count are stored before each pixel and at the end. Returns the last pixel's top
 * byte, or the operation's eax when it ran for it (eax unchanged without pixels); edx is
 * unchanged. */
uint32_t vertrix_port_render_keyed_row32(PORT_SIGNATURE);

/* Originals 0x499fb0 and 0x4a2070: the same for 16-bit targets (the pixel at 0x5bb780, two bytes
 * on). */
uint32_t vertrix_port_render_keyed_row32_499fb0(PORT_SIGNATURE);
uint32_t vertrix_port_render_keyed_row32_4a2070(PORT_SIGNATURE);

/* Original 0x492980 (eax = row routine): draw an image's rows. The globals are first moved to the
 * last row (the row count, the high word of 0x5bb750, less one, times the mask stride 0x5bb744,
 * the source stride 0x5bb74c in pixels and the target stride 0x5bb7c4 in bytes, added to the mask
 * 0x5bb7e8, the source 0x5bb76c and the target 0x5bb770). Then for each of the 16-bit count at
 * 0x5bb750 rows, from the row starts at 0x5bb7ec (0x5bbfec the current one), the pixel count
 * 0x5bc016 is the width (0x5bb752) less the row's start, the pixel addresses 0x5bb764 and 0x5bb768
 * and the mask 0x5bb7e4 are set and the routine is called with eax, edx and ecx the source,
 * target and mask one step on (those are stored too). Returns the last row's eax (the target
 * offset of the last row when there are none); edx is unchanged. */
uint32_t vertrix_port_render_image_rows(PORT_SIGNATURE);

/* Originals 0x49a690 and 0x4a2750: the same for 16-bit targets (the pixel and row at 0x5bb780 and
 * 0x5bb784, two bytes on). */
uint32_t vertrix_port_render_image_rows_49a690(PORT_SIGNATURE);
uint32_t vertrix_port_render_image_rows_4a2750(PORT_SIGNATURE);

/* Original 0x4928f0 (eax = row routine): draw rows picked through an index. For each of the 16-bit
 * count at 0x5bb752 rows (a count of 0 runs 65,536 times), the next byte at 0x5bb7d4 times
 * 0x5bb7c0, in pixels, moves the source 0x5bb76c and the target 0x5bb770 moves one stride
 * 0x5bb7c4; 0x5bb7d8 is copied to 0x5bb7dc and the pixel count 0x5bc016 is the low word of
 * 0x5bb750. The routine gets eax (0x5bb7d8 with that low word), edx the source step, ebx the
 * target, ecx itself, esi the source and edi the scale; the source and target are then stored at
 * 0x5bb764 and 0x5bb768. Returns the last routine's eax; edx is unchanged. */
uint32_t vertrix_port_render_indexed_rows(PORT_SIGNATURE);

/* Originals 0x49a600, 0x4a26c0 and 0x4aa3c0: 0x4928f0's code with the target pixel and row at
 * 0x5bb780 and 0x5bb784, 0x5bb780 and 0x5bb784, and 0x5bb778 and 0x5bb77c. */
uint32_t vertrix_port_render_indexed_rows_49a600(PORT_SIGNATURE);
uint32_t vertrix_port_render_indexed_rows_4a26c0(PORT_SIGNATURE);
uint32_t vertrix_port_render_indexed_rows_4aa3c0(PORT_SIGNATURE);

/* The registers a masked row hands its pixel operation: what the loop below left in them. */
typedef struct MaskRegisters
{
    uint32_t eax;
    uint32_t edx;
    uint32_t ebx;
    uint32_t ecx;
} MaskRegisters;

/* Original 0x492460: a masked row, drawn from its last pixel back to its first. While the row
 * start word at [0x5bbfec] is not 0, the mask byte at 0x5bb7e4 is read into bl and, when its low
 * bit is clear, the pixel operation runs; then the pixel addresses and the mask step back one
 * pixel and the word counts down. After that, the pixel operation runs for each pixel of the
 * 16-bit count at 0x5bc016, stepping back the same way. The operation gets eax, edx, ebx and ecx
 * as the loop left them (edx the mask address). Returns the eax left at the end; edx is
 * unchanged. */
uint32_t vertrix_port_render_mask_row(PORT_SIGNATURE);

/* Originals 0x49a180, 0x4a2240 and 0x4a9f40: 0x492460's code with the target pixel at 0x5bb780,
 * 0x5bb780 and 0x5bb778. */
uint32_t vertrix_port_render_mask_row_49a180(PORT_SIGNATURE);
uint32_t vertrix_port_render_mask_row_4a2240(PORT_SIGNATURE);
uint32_t vertrix_port_render_mask_row_4a9f40(PORT_SIGNATURE);

/* Original 0x4922f0: as 0x492460 for a source with an alpha byte: the pixel operation runs only
 * for pixels whose top byte is not 0 (eax that byte). */
uint32_t vertrix_port_render_mask_alpha_row(PORT_SIGNATURE);

/* Originals 0x492770, 0x49a480, 0x4a2540 and 0x4aa240: a masked row drawn backwards (the row
 * start's skipped part with mask bit 0 clear, then the row count's pixels) by the pixel operation
 * [0x5bb72c], stepping the source by the sampled steps 0x5bb7dc, with the target pixel at 0x5bb768,
 * 0x5bb780, 0x5bb780 and 0x5bb778. */
uint32_t vertrix_port_render_mask_row_back_492770(PORT_SIGNATURE);
uint32_t vertrix_port_render_mask_row_back_49a480(PORT_SIGNATURE);
uint32_t vertrix_port_render_mask_row_back_4a2540(PORT_SIGNATURE);
uint32_t vertrix_port_render_mask_row_back_4aa240(PORT_SIGNATURE);

/* Original 0x48db70: the target becomes the average of source and target. Returns the target
 * address. */
uint32_t vertrix_port_blend_average(PORT_SIGNATURE);

/* Original 0x4ab310: copy runs of pixels from [0x5bb764] to [0x5bb768]. There are [0x5bb752]
 * runs (16 bits) of [0x5bb750] pixels; after each, the source skips [0x5bb79c] pixels and the
 * target [0x5bb7c8] bytes. Returns the target pointer after the last run; edx is unchanged. */
uint32_t vertrix_port_blit_copy(PORT_SIGNATURE);

/* Original 0x4ab2a0: 0x4ab310 copying only the pixels whose top byte is non-zero. Returns the
 * source pointer after the last run; edx is unchanged. */
uint32_t vertrix_port_blit_keyed(PORT_SIGNATURE);

/* Original 0x4906a0: the source remapped as 0x48d740 does, kept at 0x5bc018, then mixed into the
 * target with the two level tables as 0x4902a0 does. Returns the target pointer; edx is
 * unchanged. */
uint32_t vertrix_port_blend_remap_levels(PORT_SIGNATURE);

/* Original 0x490b30: 0x4906a0 with the source tinted (the channel map of its entry's low byte
 * applied to the tint at 0x54d5dc) instead of remapped. */
uint32_t vertrix_port_blend_tint_levels(PORT_SIGNATURE);

/* Original 0x492dc0: the 32-bit half-blend rectangle of the renderer's state: each pixel of the
 * width (0x5bb750) by height (0x5bb752) rectangle from 0x5bb768 (rows 0x5bb7c8 bytes apart past
 * the width) becomes its half, masked to 0x7f7f7f, plus the colour at 0x54d5ec. The state is
 * stored back as the loops leave it. Returns the row skip after a row, else eax unchanged. */
uint32_t vertrix_port_rectangle_half32(PORT_SIGNATURE);

/* Original 0x4ab200(ax = x, dx = y, bx = width, cx = height): mark in the display's mask surface
 * (+0x274 of 0x544070, located by 0x478eb0) each pixel of the 32-bit source at 0x5bb764 (pitch
 * 0x5bb79c pixels) whose alpha is not 0, by setting bit 0 of its byte. */
uint32_t vertrix_port_surface_mask32(PORT_SIGNATURE);

/* Originals 0x4974c0 and 0x4977c0 (5-5-5) and 0x49f580 and 0x49f880 (5-6-5): 0x4902a0 for a
 * 16-bit target at 0x5bb780, widened into 0x5bb774 and narrowed back after the mix. Returns the
 * target pointer; edx is unchanged. */
uint32_t vertrix_port_blend_levels16_4974c0(PORT_SIGNATURE);
uint32_t vertrix_port_blend_levels16_4977c0(PORT_SIGNATURE);
uint32_t vertrix_port_blend_levels16_49f580(PORT_SIGNATURE);
uint32_t vertrix_port_blend_levels16_49f880(PORT_SIGNATURE);

/* Originals 0x4933e0 (5-5-5) and 0x49b4a0 (5-6-5): the 16-bit target pixel at [0x5bb780] becomes
 * the source colour narrowed. Returns the pixel; edx is unchanged. */
uint32_t vertrix_port_pixel16_copy_4933e0(PORT_SIGNATURE);
uint32_t vertrix_port_pixel16_copy_49b4a0(PORT_SIGNATURE);

/* Originals 0x4935c0 (5-5-5) and 0x49b680 (5-6-5): the target becomes the source halved (masked to
 * 0x7f7f7f) plus the colour at 0x54d5ec, kept at 0x5bb774. Returns the pixel; edx is unchanged. */
uint32_t vertrix_port_pixel16_half_plus_4935c0(PORT_SIGNATURE);
uint32_t vertrix_port_pixel16_half_plus_49b680(PORT_SIGNATURE);

/* Originals 0x493e70 (5-5-5) and 0x49bf30 (5-6-5): the target becomes the inverted source (its low
 * 24 bits kept at 0x5bb774). Returns the pixel; edx is unchanged. */
uint32_t vertrix_port_pixel16_invert_493e70(PORT_SIGNATURE);
uint32_t vertrix_port_pixel16_invert_49bf30(PORT_SIGNATURE);

/* Originals 0x495ac0 (5-5-5) and 0x49db80 (5-6-5): the inverted source (low 24 bits, kept at
 * 0x5bc018) halved plus the colour at 0x54d5ec, kept at 0x5bb774. Returns the pixel; edx is
 * unchanged. */
uint32_t vertrix_port_pixel16_invert_half_plus_495ac0(PORT_SIGNATURE);
uint32_t vertrix_port_pixel16_invert_half_plus_49db80(PORT_SIGNATURE);

/* Originals 0x493970 (5-5-5) and 0x49ba30 (5-6-5): the target becomes the average of the widened
 * target and the source (each halved and masked to 0x7f7f7f), kept at 0x5bb774. Returns the target
 * address; edx is unchanged. */
uint32_t vertrix_port_pixel16_average_493970(PORT_SIGNATURE);
uint32_t vertrix_port_pixel16_average_49ba30(PORT_SIGNATURE);

/* Originals 0x493ba0 (5-5-5) and 0x49bc60 (5-6-5): the same code as 0x493970. */
uint32_t vertrix_port_pixel16_average_493ba0(PORT_SIGNATURE);
uint32_t vertrix_port_pixel16_average_49bc60(PORT_SIGNATURE);

/* Originals 0x493ec0 (5-5-5) and 0x49bf80 (5-6-5): the target becomes its widened colour inverted
 * (the low 24 bits kept at 0x5bb774). Returns the pixel; edx is unchanged. */
uint32_t vertrix_port_pixel16_invert_target_493ec0(PORT_SIGNATURE);
uint32_t vertrix_port_pixel16_invert_target_49bf80(PORT_SIGNATURE);

/* Originals 0x494bc0 (5-5-5) and 0x49cc80 (5-6-5): the target becomes the sum of the source's and
 * its own quarters (masked to 0x3f3f3f) and the colour at 0x54d5ec, kept at 0x5bb774. Returns the
 * target address; edx is unchanged. */
uint32_t vertrix_port_pixel16_quarters_plus_494bc0(PORT_SIGNATURE);
uint32_t vertrix_port_pixel16_quarters_plus_49cc80(PORT_SIGNATURE);

/* Originals 0x495d50 (5-5-5) and 0x49de10 (5-6-5): the inverted widened target (low 24 bits, kept
 * at 0x5bc018) halved plus the colour at 0x54d5ec, kept at 0x5bb774. Returns the target address;
 * edx is unchanged. */
uint32_t vertrix_port_pixel16_invert_target_half_plus_495d50(PORT_SIGNATURE);
uint32_t vertrix_port_pixel16_invert_target_half_plus_49de10(PORT_SIGNATURE);

/* Originals 0x493500 (5-5-5) and 0x49b5c0 (5-6-5): the target becomes the source remapped through
 * fixed channels (as 0x48e900 does), kept at 0x5bb774. Returns the pixel; edx is unchanged. */
uint32_t vertrix_port_pixel16_tint_493500(PORT_SIGNATURE);
uint32_t vertrix_port_pixel16_tint_49b5c0(PORT_SIGNATURE);

/* Originals 0x493c30 (5-5-5) and 0x49bcf0 (5-6-5): saturating add of the source to the widened
 * target (the low 24 bits kept at 0x5bb774). Returns the target address; edx is unchanged. */
uint32_t vertrix_port_pixel16_add_493c30(PORT_SIGNATURE);
uint32_t vertrix_port_pixel16_add_49bcf0(PORT_SIGNATURE);

/* Originals 0x493cf0 (5-5-5) and 0x49bdb0 (5-6-5): saturating subtract of the source from the
 * widened target (the low 24 bits kept at 0x5bb774). Returns the target address; edx is unchanged.
 */
uint32_t vertrix_port_pixel16_subtract_493cf0(PORT_SIGNATURE);
uint32_t vertrix_port_pixel16_subtract_49bdb0(PORT_SIGNATURE);

/* Originals 0x493db0 (5-5-5) and 0x49be70 (5-6-5): the target becomes the source less the widened
 * target, each channel stopping at 0 (the low 24 bits kept at 0x5bb774). Returns the target
 * address; edx is unchanged. */
uint32_t vertrix_port_pixel16_subtract_from_493db0(PORT_SIGNATURE);
uint32_t vertrix_port_pixel16_subtract_from_49be70(PORT_SIGNATURE);

/* Originals 0x495060 (5-5-5) and 0x49d120 (5-6-5): saturating add to the widened target of the
 * source halved plus the colour at 0x54d5ec (kept at 0x5bc018); the low 24 bits are kept at
 * 0x5bb774. Returns the pixel; edx is unchanged. */
uint32_t vertrix_port_pixel16_half_plus_add_495060(PORT_SIGNATURE);
uint32_t vertrix_port_pixel16_half_plus_add_49d120(PORT_SIGNATURE);

/* Originals 0x4953f0 (5-5-5) and 0x49d4b0 (5-6-5): the same with a saturating subtract from the
 * target. Returns the pixel; edx is unchanged. */
uint32_t vertrix_port_pixel16_half_plus_subtract_4953f0(PORT_SIGNATURE);
uint32_t vertrix_port_pixel16_half_plus_subtract_49d4b0(PORT_SIGNATURE);

/* Originals 0x495780 (5-5-5) and 0x49d840 (5-6-5): the same with the target subtracted from the
 * halved colour. Returns the pixel; edx is unchanged. */
uint32_t vertrix_port_pixel16_half_plus_subtract_from_495780(PORT_SIGNATURE);
uint32_t vertrix_port_pixel16_half_plus_subtract_from_49d840(PORT_SIGNATURE);

/* Originals 0x493420 (5-5-5) and 0x49b4e0 (5-6-5): the target becomes the remapped source, kept at
 * 0x5bb774. Returns the pixel; edx is unchanged. */
uint32_t vertrix_port_pixel16_remap_493420(PORT_SIGNATURE);
uint32_t vertrix_port_pixel16_remap_49b4e0(PORT_SIGNATURE);

/* Originals 0x4959e0 (5-5-5) and 0x49daa0 (5-6-5): the inverted source (low 24 bits kept at
 * 0x5bc018) remapped through fixed channels, kept at 0x5bb774. Returns the target address; edx is
 * unchanged. */
uint32_t vertrix_port_pixel16_invert_tint_4959e0(PORT_SIGNATURE);
uint32_t vertrix_port_pixel16_invert_tint_49daa0(PORT_SIGNATURE);

/* Originals 0x493720 (5-5-5) and 0x49b7e0 (5-6-5): the source halved plus the colour at 0x54d5ec,
 * then remapped, kept at 0x5bb774. Returns the pixel; edx is unchanged. */
uint32_t vertrix_port_pixel16_half_plus_remap_493720(PORT_SIGNATURE);
uint32_t vertrix_port_pixel16_half_plus_remap_49b7e0(PORT_SIGNATURE);

/* Originals 0x498570 (5-5-5) and 0x4a0630 (5-6-5): the map the source's colour entry selects
 * (stored at 0x54d5d0) applied to the bytes 3, 2 and 1 of the dword the pointer at entry
 * [0x54d5f0] of the table at [0x54cdcc] points to (stored at 0x54d5d4), kept at 0x5bb774. Returns
 * the pixel; edx is unchanged. */
uint32_t vertrix_port_pixel16_fixed_entry_498570(PORT_SIGNATURE);
uint32_t vertrix_port_pixel16_fixed_entry_4a0630(PORT_SIGNATURE);

/* Originals 0x494840 (5-5-5) and 0x49c900 (5-6-5): the target becomes the remapped source (kept at
 * 0x5bc018) inverted, its low 24 bits kept at 0x5bb774. Returns the target address; edx is
 * unchanged. */
uint32_t vertrix_port_pixel16_remap_invert_494840(PORT_SIGNATURE);
uint32_t vertrix_port_pixel16_remap_invert_49c900(PORT_SIGNATURE);

/* Originals 0x498470 (5-5-5) and 0x4a0530 (5-6-5): the source's entry index (stored at 0x54d5e4)
 * selects both the map (stored at 0x54d5d0) and, through the byte table at [0x54b804], the pointer
 * in the table at [0x54cdcc] to the dword (stored at 0x54d5d4) whose bytes 3, 2 and 1 the map is
 * applied to; the colour is kept at 0x5bb774. Returns the pixel; edx is unchanged. */
uint32_t vertrix_port_pixel16_paired_entry_498470(PORT_SIGNATURE);
uint32_t vertrix_port_pixel16_paired_entry_4a0530(PORT_SIGNATURE);

/* Originals 0x493610 (5-5-5) and 0x49b6d0 (5-6-5): the target becomes the source remapped half way
 * to the fixed channels (as 0x48d8c0 does), kept at 0x5bb774. Returns the pixel; edx is unchanged.
 */
uint32_t vertrix_port_pixel16_half_tint_493610(PORT_SIGNATURE);
uint32_t vertrix_port_pixel16_half_tint_49b6d0(PORT_SIGNATURE);

/* Originals 0x495c40 (5-5-5) and 0x49dd00 (5-6-5): the inverted widened target (low 24 bits kept
 * at 0x5bc018) remapped through fixed channels, kept at 0x5bb774. Returns the target address; edx
 * is unchanged. */
uint32_t vertrix_port_pixel16_invert_target_tint_495c40(PORT_SIGNATURE);
uint32_t vertrix_port_pixel16_invert_target_tint_49dd00(PORT_SIGNATURE);

/* Originals 0x498660 (5-5-5) and 0x4a0720 (5-6-5): the source halved plus the colour at 0x54d5ec
 * (kept at 0x5bc018), remapped as 0x498470 does and kept at 0x5bb774. Returns the pixel; edx is
 * unchanged. */
uint32_t vertrix_port_pixel16_half_plus_paired_498660(PORT_SIGNATURE);
uint32_t vertrix_port_pixel16_half_plus_paired_4a0720(PORT_SIGNATURE);

/* Originals 0x499350 (5-5-5) and 0x4a1410 (5-6-5): the source remapped as 0x498470 does (kept at
 * 0x5bc018) and inverted, its low 24 bits kept at 0x5bb774. Returns the pixel; edx is unchanged. */
uint32_t vertrix_port_pixel16_paired_invert_499350(PORT_SIGNATURE);
uint32_t vertrix_port_pixel16_paired_invert_4a1410(PORT_SIGNATURE);

/* Originals 0x494e10 (5-5-5) and 0x49ced0 (5-6-5): the target becomes the average of the widened
 * target and the source remapped through fixed channels (kept at 0x5bc018), kept at 0x5bb774.
 * Returns the target address; edx is unchanged. */
uint32_t vertrix_port_pixel16_tint_average_494e10(PORT_SIGNATURE);
uint32_t vertrix_port_pixel16_tint_average_49ced0(PORT_SIGNATURE);

/* Originals 0x495b20 (5-5-5) and 0x49dbe0 (5-6-5): the inverted source (low 24 bits kept at
 * 0x5bc018) remapped half way to the fixed channels, kept at 0x5bb774. Returns the target address;
 * edx is unchanged. */
uint32_t vertrix_port_pixel16_invert_half_tint_495b20(PORT_SIGNATURE);
uint32_t vertrix_port_pixel16_invert_half_tint_49dbe0(PORT_SIGNATURE);

/* Originals 0x496cd0 (5-5-5) and 0x49ed90 (5-6-5): the inverted source halved plus the colour at
 * 0x54d5ec (kept at 0x5bc018), then remapped and kept at 0x5bb774. Returns the target address; edx
 * is unchanged. */
uint32_t vertrix_port_pixel16_invert_half_plus_remap_496cd0(PORT_SIGNATURE);
uint32_t vertrix_port_pixel16_invert_half_plus_remap_49ed90(PORT_SIGNATURE);

/* Originals 0x494f30 (5-5-5) and 0x49cff0 (5-6-5): saturating add to the widened target of the
 * source remapped through fixed channels (kept at 0x5bc018); the low 24 bits are kept at 0x5bb774.
 * Returns the pixel; edx is unchanged. */
uint32_t vertrix_port_pixel16_tint_add_494f30(PORT_SIGNATURE);
uint32_t vertrix_port_pixel16_tint_add_49cff0(PORT_SIGNATURE);

/* Originals 0x4952c0 (5-5-5) and 0x49d380 (5-6-5): the same with a saturating subtract from the
 * target. Returns the pixel; edx is unchanged. */
uint32_t vertrix_port_pixel16_tint_subtract_4952c0(PORT_SIGNATURE);
uint32_t vertrix_port_pixel16_tint_subtract_49d380(PORT_SIGNATURE);

/* Originals 0x495650 (5-5-5) and 0x49d710 (5-6-5): the same with the target subtracted from the
 * remapped colour. Returns the pixel; edx is unchanged. */
uint32_t vertrix_port_pixel16_tint_subtract_from_495650(PORT_SIGNATURE);
uint32_t vertrix_port_pixel16_tint_subtract_from_49d710(PORT_SIGNATURE);

/* Originals 0x496350 (5-5-5) and 0x49e410 (5-6-5): the target becomes its own widened colour
 * remapped through fixed channels, kept at 0x5bb774; the source's colour entry is stored at
 * 0x54d5d4. Returns the target address; edx is unchanged. */
uint32_t vertrix_port_pixel16_target_tint_496350(PORT_SIGNATURE);
uint32_t vertrix_port_pixel16_target_tint_49e410(PORT_SIGNATURE);

/* Originals 0x493f40 (5-5-5) and 0x49c000 (5-6-5): the widened target's colour entry (stored at
 * 0x54d5d4) remapped through the map the source's entry selects (stored at 0x54d5d0), kept at
 * 0x5bb774. Returns the target address; edx is unchanged. */
uint32_t vertrix_port_pixel16_cross_remap_493f40(PORT_SIGNATURE);
uint32_t vertrix_port_pixel16_cross_remap_49c000(PORT_SIGNATURE);

/* Originals 0x4941d0 (5-5-5) and 0x49c290 (5-6-5): the average of the widened target and the
 * source, remapped and kept at 0x5bb774. Returns the target address; edx is unchanged. */
uint32_t vertrix_port_pixel16_average_remap_4941d0(PORT_SIGNATURE);
uint32_t vertrix_port_pixel16_average_remap_49c290(PORT_SIGNATURE);

/* Originals 0x494310 (5-5-5) and 0x49c3d0 (5-6-5): the average of the widened target and the
 * remapped source (kept at 0x5bc018), kept at 0x5bb774. Returns the target address; edx is
 * unchanged. */
uint32_t vertrix_port_pixel16_remap_average_494310(PORT_SIGNATURE);
uint32_t vertrix_port_pixel16_remap_average_49c3d0(PORT_SIGNATURE);

/* Originals 0x494940 (5-5-5) and 0x49ca00 (5-6-5): the widened target remapped (kept at 0x5bc018)
 * and inverted, its low 24 bits kept at 0x5bb774. Returns the target address; edx is unchanged. */
uint32_t vertrix_port_pixel16_target_remap_invert_494940(PORT_SIGNATURE);
uint32_t vertrix_port_pixel16_target_remap_invert_49ca00(PORT_SIGNATURE);

/* Originals 0x494a80 (5-5-5) and 0x49cb40 (5-6-5): the fixed channels remapped through the map
 * numbered by the mean (rounded down) of the source's and the widened target's entry bytes (the
 * map stored at 0x54d5d0), kept at 0x5bb774. Returns the target address; edx is unchanged. */
uint32_t vertrix_port_pixel16_mean_map_tint_494a80(PORT_SIGNATURE);
uint32_t vertrix_port_pixel16_mean_map_tint_49cb40(PORT_SIGNATURE);

/* Originals 0x495f40 (5-5-5) and 0x49e000 (5-6-5): the fixed channels remapped through the map the
 * source's entry selects (stored at 0x54d5d0), kept at 0x5bb774; the widened target's entry is
 * stored at 0x54d5d4. Returns the target address; edx is unchanged. */
uint32_t vertrix_port_pixel16_source_tint_495f40(PORT_SIGNATURE);
uint32_t vertrix_port_pixel16_source_tint_49e000(PORT_SIGNATURE);

/* Originals 0x497da0 (5-5-5) and 0x49fe60 (5-6-5): each channel becomes half the sum of the
 * source's level (table at [0x55f1f0]), the widened target's level (table at [0x55f1f4]) and the
 * channel's byte at 0x54d5e8, 0x54d5e9 or 0x54d5ea (the halves or-ed into place); the colour is
 * kept at 0x5bb774. Returns the target address; edx is unchanged. */
uint32_t vertrix_port_pixel16_levels_bias_497da0(PORT_SIGNATURE);
uint32_t vertrix_port_pixel16_levels_bias_49fe60(PORT_SIGNATURE);

/* Originals 0x499460 (5-5-5) and 0x4a1520 (5-6-5): the widened target remapped as 0x498470 does
 * (kept at 0x5bc018) and inverted, its low 24 bits kept at 0x5bb774. Returns the pixel; edx is
 * unchanged. */
uint32_t vertrix_port_pixel16_target_paired_invert_499460(PORT_SIGNATURE);
uint32_t vertrix_port_pixel16_target_paired_invert_4a1520(PORT_SIGNATURE);

/* Originals 0x494080 (5-5-5) and 0x49c140 (5-6-5): the source's colour entry (stored at 0x54d5d4)
 * remapped through the map the widened target's entry selects (stored at 0x54d5d0), kept at
 * 0x5bb774. Returns the target address; edx is unchanged. */
uint32_t vertrix_port_pixel16_target_cross_remap_494080(PORT_SIGNATURE);
uint32_t vertrix_port_pixel16_target_cross_remap_49c140(PORT_SIGNATURE);

/* Originals 0x494450 (5-5-5) and 0x49c510 (5-6-5): saturating add to the widened target of the
 * remapped source (kept at 0x5bc018); the low 24 bits are kept at 0x5bb774. Returns the pixel; edx
 * is unchanged. */
uint32_t vertrix_port_pixel16_remap_add_494450(PORT_SIGNATURE);
uint32_t vertrix_port_pixel16_remap_add_49c510(PORT_SIGNATURE);

/* Originals 0x4945a0 (5-5-5) and 0x49c660 (5-6-5): the same with a saturating subtract from the
 * target. Returns the pixel; edx is unchanged. */
uint32_t vertrix_port_pixel16_remap_subtract_4945a0(PORT_SIGNATURE);
uint32_t vertrix_port_pixel16_remap_subtract_49c660(PORT_SIGNATURE);

/* Originals 0x4946f0 (5-5-5) and 0x49c7b0 (5-6-5): the same with the target subtracted from the
 * remapped colour. Returns the pixel; edx is unchanged. */
uint32_t vertrix_port_pixel16_remap_subtract_from_4946f0(PORT_SIGNATURE);
uint32_t vertrix_port_pixel16_remap_subtract_from_49c7b0(PORT_SIGNATURE);

/* Originals 0x495df0 (5-5-5) and 0x49deb0 (5-6-5): the inverted widened target (low 24 bits kept
 * at 0x5bc018) remapped half way to the fixed channels, kept at 0x5bb774. Returns the target
 * address; edx is unchanged. */
uint32_t vertrix_port_pixel16_invert_target_half_tint_495df0(PORT_SIGNATURE);
uint32_t vertrix_port_pixel16_invert_target_half_tint_49deb0(PORT_SIGNATURE);

/* Originals 0x496750 (5-5-5) and 0x49e810 (5-6-5): the sum of the widened target's and the
 * source's quarters (masked to 0x3f3f3f) and the colour at 0x54d5ec, remapped and kept at
 * 0x5bb774. Returns the target address; edx is unchanged. */
uint32_t vertrix_port_pixel16_quarters_plus_remap_496750(PORT_SIGNATURE);
uint32_t vertrix_port_pixel16_quarters_plus_remap_49e810(PORT_SIGNATURE);

/* Originals 0x496df0 (5-5-5) and 0x49eeb0 (5-6-5): the inverted widened target halved plus the
 * colour at 0x54d5ec (kept at 0x5bc018), then remapped and kept at 0x5bb774. Returns the target
 * address; edx is unchanged. */
uint32_t vertrix_port_pixel16_invert_target_half_plus_remap_496df0(PORT_SIGNATURE);
uint32_t vertrix_port_pixel16_invert_target_half_plus_remap_49eeb0(PORT_SIGNATURE);

/* Originals 0x497c50 (5-5-5) and 0x49fd10 (5-6-5): the fixed channels remapped through the map
 * numbered as 0x4901a0 numbers it (the source's entry byte through [0x5785f8] plus the widened
 * target's through [0x5785fc]; stored at 0x54d5d0), kept at 0x5bb774. Returns the target address;
 * edx is unchanged. */
uint32_t vertrix_port_pixel16_shade_tint_497c50(PORT_SIGNATURE);
uint32_t vertrix_port_pixel16_shade_tint_49fd10(PORT_SIGNATURE);

/* Originals 0x493810 (5-5-5) and 0x49b8d0 (5-6-5): the source's colour entry (stored at 0x54d5d4)
 * remapped through the map numbered by the mean (rounded down) of its low byte and the widened
 * target's entry byte (stored at 0x54d5d0), kept at 0x5bb774. Returns the target address; edx is
 * unchanged. */
uint32_t vertrix_port_pixel16_mean_map_remap_493810(PORT_SIGNATURE);
uint32_t vertrix_port_pixel16_mean_map_remap_49b8d0(PORT_SIGNATURE);

/* Originals 0x496080 (5-5-5) and 0x49e140 (5-6-5): the colour of 0x493f40 (kept at 0x5bc018)
 * halved plus the colour at 0x54d5ec, kept at 0x5bb774. Returns the target address; edx is
 * unchanged. */
uint32_t vertrix_port_pixel16_cross_remap_half_plus_496080(PORT_SIGNATURE);
uint32_t vertrix_port_pixel16_cross_remap_half_plus_49e140(PORT_SIGNATURE);

/* Originals 0x496480 (5-5-5) and 0x49e540 (5-6-5): the colour of 0x494080 (kept at 0x5bc018)
 * halved plus the colour at 0x54d5ec, kept at 0x5bb774. Returns the target address; edx is
 * unchanged. */
uint32_t vertrix_port_pixel16_target_cross_remap_half_plus_496480(PORT_SIGNATURE);
uint32_t vertrix_port_pixel16_target_cross_remap_half_plus_49e540(PORT_SIGNATURE);

/* Originals 0x496a10 (5-5-5) and 0x49ead0 (5-6-5): saturating subtract from the widened target of
 * the colour of 0x493720 (kept at 0x5bc018); the low 24 bits are kept at 0x5bb774. Returns the
 * pixel; edx is unchanged. */
uint32_t vertrix_port_pixel16_half_plus_remap_subtract_496a10(PORT_SIGNATURE);
uint32_t vertrix_port_pixel16_half_plus_remap_subtract_49ead0(PORT_SIGNATURE);

/* Originals 0x496b70 (5-5-5) and 0x49ec30 (5-6-5): the same with the target subtracted from that
 * colour. Returns the pixel; edx is unchanged. */
uint32_t vertrix_port_pixel16_half_plus_remap_subtract_from_496b70(PORT_SIGNATURE);
uint32_t vertrix_port_pixel16_half_plus_remap_subtract_from_49ec30(PORT_SIGNATURE);

/* Originals 0x499090 (5-5-5) and 0x4a1150 (5-6-5): saturating subtract from the widened target of
 * the source remapped as 0x498470 does (kept at 0x5bc018); the low 24 bits are kept at 0x5bb774.
 * Returns the pixel; edx is unchanged. */
uint32_t vertrix_port_pixel16_paired_subtract_499090(PORT_SIGNATURE);
uint32_t vertrix_port_pixel16_paired_subtract_4a1150(PORT_SIGNATURE);

/* Originals 0x4991f0 (5-5-5) and 0x4a12b0 (5-6-5): the same as 0x499090 with the target subtracted
 * from the remapped colour. Returns the pixel; edx is unchanged. */
uint32_t vertrix_port_pixel16_paired_subtract_from_4991f0(PORT_SIGNATURE);
uint32_t vertrix_port_pixel16_paired_subtract_from_4a12b0(PORT_SIGNATURE);

/* Originals 0x4995a0 (5-5-5) and 0x4a1660 (5-6-5): the map the source's entry selects (stored at
 * 0x54d5d0) applied to the dword picked as 0x498470 picks it from the widened target's entry index
 * (stored at 0x54d5d4), kept at 0x5bb774. Returns the target address; edx is unchanged. */
uint32_t vertrix_port_pixel16_paired_cross_4995a0(PORT_SIGNATURE);
uint32_t vertrix_port_pixel16_paired_cross_4a1660(PORT_SIGNATURE);

/* Originals 0x499700 (5-5-5) and 0x4a17c0 (5-6-5): the same with the map from the widened target
 * and the dword from the source. Returns the target address; edx is unchanged. */
uint32_t vertrix_port_pixel16_target_paired_cross_499700(PORT_SIGNATURE);
uint32_t vertrix_port_pixel16_target_paired_cross_4a17c0(PORT_SIGNATURE);

/* Originals 0x4961e0 (5-5-5) and 0x49e2a0 (5-6-5): the widened target's colour entry (stored at
 * 0x54d5d4) remapped half way to the fixed channels through the map the source's entry selects
 * (stored at 0x54d5d0), kept at 0x5bb774. Returns the target address; edx is unchanged. */
uint32_t vertrix_port_pixel16_cross_half_tint_4961e0(PORT_SIGNATURE);
uint32_t vertrix_port_pixel16_cross_half_tint_49e2a0(PORT_SIGNATURE);

/* Originals 0x4965e0 (5-5-5) and 0x49e6a0 (5-6-5): the same with the map from the widened target
 * and the entry from the source. Returns the target address; edx is unchanged. */
uint32_t vertrix_port_pixel16_target_cross_half_tint_4965e0(PORT_SIGNATURE);
uint32_t vertrix_port_pixel16_target_cross_half_tint_49e6a0(PORT_SIGNATURE);

/* Originals 0x4968a0 (5-5-5) and 0x49e960 (5-6-5): saturating add to the widened target of the
 * colour of 0x493720 (kept at 0x5bc018); the low 24 bits are kept at 0x5bb774. Returns the pixel;
 * edx is unchanged. */
uint32_t vertrix_port_pixel16_half_plus_remap_add_4968a0(PORT_SIGNATURE);
uint32_t vertrix_port_pixel16_half_plus_remap_add_49e960(PORT_SIGNATURE);

/* Originals 0x498910 (5-5-5) and 0x4a09d0 (5-6-5): the map numbered by the mean (rounded down) of
 * the source's and the widened target's entry bytes (the source's entry stored at 0x54d5d4 first,
 * the map at 0x54d5d0) applied to the dword picked as 0x498470 picks it from the source's entry
 * index (the dword stored at 0x54d5d4, the index at 0x54d5e4), kept at 0x5bb774. Returns the
 * target address; edx is unchanged. */
uint32_t vertrix_port_pixel16_mean_map_paired_498910(PORT_SIGNATURE);
uint32_t vertrix_port_pixel16_mean_map_paired_4a09d0(PORT_SIGNATURE);

/* Originals 0x498a80 (5-5-5) and 0x4a0b40 (5-6-5): the average of the widened target and the
 * source (kept at 0x5bc018) remapped as 0x498470 does, kept at 0x5bb774. Returns the target
 * address; edx is unchanged. */
uint32_t vertrix_port_pixel16_average_paired_498a80(PORT_SIGNATURE);
uint32_t vertrix_port_pixel16_average_paired_4a0b40(PORT_SIGNATURE);

/* Originals 0x498db0 (5-5-5) and 0x4a0e70 (5-6-5): the average of the widened target and the
 * source remapped as 0x498470 does (kept at 0x5bc018), kept at 0x5bb774. Returns the target
 * address; edx is unchanged. */
uint32_t vertrix_port_pixel16_paired_average_498db0(PORT_SIGNATURE);
uint32_t vertrix_port_pixel16_paired_average_4a0e70(PORT_SIGNATURE);

/* Originals 0x498f20 (5-5-5) and 0x4a0fe0 (5-6-5): the same as 0x499090 with a saturating add.
 * Returns the pixel; edx is unchanged. */
uint32_t vertrix_port_pixel16_paired_add_498f20(PORT_SIGNATURE);
uint32_t vertrix_port_pixel16_paired_add_4a0fe0(PORT_SIGNATURE);

/* Originals 0x497340 (5-5-5) and 0x49f400 (5-6-5): 0x4901a0 for the 16-bit target: the source's
 * colour entry (stored at 0x54d5d4) remapped through the map numbered by its low byte's word in
 * [0x5785f8] plus the widened target's entry byte's word in [0x5785fc] (signed; stored at
 * 0x54d5d0), kept at 0x5bb774. Returns the target address; edx is unchanged. */
uint32_t vertrix_port_pixel16_shade_497340(PORT_SIGNATURE);
uint32_t vertrix_port_pixel16_shade_49f400(PORT_SIGNATURE);

/* Originals 0x495130 (5-5-5) and 0x49d1f0 (5-6-5): saturating add to the widened target of the
 * source remapped half way to the fixed channels (kept at 0x5bc018); the low 24 bits are kept at
 * 0x5bb774. Returns the pixel; edx is unchanged. */
uint32_t vertrix_port_pixel16_half_tint_add_495130(PORT_SIGNATURE);
uint32_t vertrix_port_pixel16_half_tint_add_49d1f0(PORT_SIGNATURE);

/* Originals 0x4954c0 (5-5-5) and 0x49d580 (5-6-5): the same as 0x495130 with a saturating subtract
 * from the target. Returns the pixel; edx is unchanged. */
uint32_t vertrix_port_pixel16_half_tint_subtract_4954c0(PORT_SIGNATURE);
uint32_t vertrix_port_pixel16_half_tint_subtract_49d580(PORT_SIGNATURE);

/* Originals 0x495850 (5-5-5) and 0x49d910 (5-6-5): the same as 0x495130 with the target subtracted
 * from the remapped colour. Returns the pixel; edx is unchanged. */
uint32_t vertrix_port_pixel16_half_tint_subtract_from_495850(PORT_SIGNATURE);
uint32_t vertrix_port_pixel16_half_tint_subtract_from_49d910(PORT_SIGNATURE);

/* Originals 0x4980f0 (5-5-5) and 0x4a01b0 (5-6-5): the widened target (stored at 0x5bb774 first)
 * mixed by the two level tables of 0x4902a0 with the source remapped through fixed channels (kept
 * at 0x5bc018); the mix is kept at 0x5bb774. Returns the target address; edx is unchanged. */
uint32_t vertrix_port_pixel16_tint_levels_4980f0(PORT_SIGNATURE);
uint32_t vertrix_port_pixel16_tint_levels_4a01b0(PORT_SIGNATURE);

/* Originals 0x499860 (5-5-5) and 0x4a1920 (5-6-5): the map numbered as 0x497340 numbers it (the
 * source's entry stored at 0x54d5d4 first, the map at 0x54d5d0) applied to the dword picked as
 * 0x498470 picks it from the source's entry index (the dword stored at 0x54d5d4, the index at
 * 0x54d5e4), kept at 0x5bb774. Returns the target address; edx is unchanged. */
uint32_t vertrix_port_pixel16_shade_paired_499860(PORT_SIGNATURE);
uint32_t vertrix_port_pixel16_shade_paired_4a1920(PORT_SIGNATURE);

/* Originals 0x493a00 (5-5-5) and 0x49bac0 (5-6-5): the map of the source's colour entry (the entry
 * stored at 0x54d5d4, the map at 0x54d5d0) applied to the means (rounded down) of that entry's
 * bytes 3, 2 and 1 and the widened target's entry's (stored at 0x54d5d8), kept at 0x5bb774.
 * Returns the target address; edx is unchanged. */
uint32_t vertrix_port_pixel16_entry_mean_493a00(PORT_SIGNATURE);
uint32_t vertrix_port_pixel16_entry_mean_49bac0(PORT_SIGNATURE);

/* Originals 0x498770 (5-5-5) and 0x4a0830 (5-6-5): the source remapped half way to the fixed
 * channels; the map used is applied again to the dword picked as 0x498470 picks it from that
 * colour's entry index (stored at 0x54d5d4), kept at 0x5bb774. Returns the target address; edx is
 * unchanged. */
uint32_t vertrix_port_pixel16_half_tint_fixed_498770(PORT_SIGNATURE);
uint32_t vertrix_port_pixel16_half_tint_fixed_4a0830(PORT_SIGNATURE);

/* Originals 0x494c60 (5-5-5) and 0x49cd20 (5-6-5): as 0x493a00 with each mean taken again with the
 * fixed channel (0x54d5dc, 0x54d5de and 0x54d5e0) before the map is applied. Returns the target
 * address; edx is unchanged. */
uint32_t vertrix_port_pixel16_entry_mean_tint_494c60(PORT_SIGNATURE);
uint32_t vertrix_port_pixel16_entry_mean_tint_49cd20(PORT_SIGNATURE);

/* Originals 0x4978d0 (5-5-5) and 0x49f990 (5-6-5): 0x490560 for the 16-bit target: the widened
 * target (stored at 0x5bb774 first) mixed with the source by the two level tables and then
 * remapped, kept at 0x5bb774. Returns the target address; edx is unchanged. */
uint32_t vertrix_port_pixel16_levels_remap_4978d0(PORT_SIGNATURE);
uint32_t vertrix_port_pixel16_levels_remap_49f990(PORT_SIGNATURE);

/* Originals 0x497a90 (5-5-5) and 0x49fb50 (5-6-5): 0x4906a0 for the 16-bit target: the widened
 * target (stored at 0x5bb774 first) mixed by the two level tables with the remapped source (kept
 * at 0x5bc018), kept at 0x5bb774. Returns the target address; edx is unchanged. */
uint32_t vertrix_port_pixel16_remap_levels_497a90(PORT_SIGNATURE);
uint32_t vertrix_port_pixel16_remap_levels_49fb50(PORT_SIGNATURE);

/* Originals 0x498bf0 (5-5-5) and 0x4a0cb0 (5-6-5): the map of the source's colour entry (the entry
 * stored at 0x54d5d4 first, the map at 0x54d5d0) applied to the means (rounded down) of the bytes
 * 3, 2 and 1 of the dword picked as 0x498470 picks it (stored at 0x54d5d4; the index at 0x54d5e4)
 * and of the widened target's entry (stored at 0x54d5d8), kept at 0x5bb774. Returns the target
 * address; edx is unchanged. */
uint32_t vertrix_port_pixel16_fixed_entry_mean_498bf0(PORT_SIGNATURE);
uint32_t vertrix_port_pixel16_fixed_entry_mean_4a0cb0(PORT_SIGNATURE);

/* Originals 0x496f40 (5-5-5) and 0x49f000 (5-6-5): the widened target's colour entry (stored at
 * 0x54d5d4) through the map the source's entry selects (not stored), halved plus the colour at
 * 0x54d5ec (kept at 0x5bc018), then remapped and kept at 0x5bb774. Returns the target address; edx
 * is unchanged. */
uint32_t vertrix_port_pixel16_cross_half_plus_remap_496f40(PORT_SIGNATURE);
uint32_t vertrix_port_pixel16_cross_half_plus_remap_49f000(PORT_SIGNATURE);

/* Originals 0x497140 (5-5-5) and 0x49f200 (5-6-5): the same with the map from the widened target
 * and the entry from the source. Returns the target address; edx is unchanged. */
uint32_t vertrix_port_pixel16_target_cross_half_plus_remap_497140(PORT_SIGNATURE);
uint32_t vertrix_port_pixel16_target_cross_half_plus_remap_49f200(PORT_SIGNATURE);

/* Originals 0x4975d0 (5-5-5) and 0x49f690 (5-6-5): the map of the source's colour entry (the entry
 * stored at 0x54d5d4, the map at 0x54d5d0) applied to the sums of that entry's bytes 3, 2 and 1
 * through the table at [0x55f1f0] and the widened target's entry's (stored at 0x54d5d8) through
 * the table at [0x55f1f4], kept at 0x5bb774. Returns the target address; edx is unchanged. */
uint32_t vertrix_port_pixel16_entry_levels_4975d0(PORT_SIGNATURE);
uint32_t vertrix_port_pixel16_entry_levels_49f690(PORT_SIGNATURE);

/* Originals 0x4999f0 (5-5-5) and 0x4a1ab0 (5-6-5): the widened target (stored at 0x5bb774) mixed
 * with the source by the two level tables (stored there again), then remapped as 0x498470 does and
 * kept at 0x5bb774. Returns the target address; edx is unchanged. */
uint32_t vertrix_port_pixel16_levels_paired_4999f0(PORT_SIGNATURE);
uint32_t vertrix_port_pixel16_levels_paired_4a1ab0(PORT_SIGNATURE);

/* Originals 0x499dd0 (5-5-5) and 0x4a1e90 (5-6-5): the widened target (stored at 0x5bb774 first)
 * mixed by the two level tables with the source remapped as 0x498470 does (kept at 0x5bc018), kept
 * at 0x5bb774. Returns the target address; edx is unchanged. */
uint32_t vertrix_port_pixel16_paired_levels_499dd0(PORT_SIGNATURE);
uint32_t vertrix_port_pixel16_paired_levels_4a1e90(PORT_SIGNATURE);

/* Originals 0x498280 (5-5-5) and 0x4a0340 (5-6-5): the colour of 0x497da0, remapped and kept at
 * 0x5bb774. Returns the target address; edx is unchanged. */
uint32_t vertrix_port_pixel16_levels_bias_remap_498280(PORT_SIGNATURE);
uint32_t vertrix_port_pixel16_levels_bias_remap_4a0340(PORT_SIGNATURE);

/* Originals 0x497ee0 (5-5-5) and 0x49ffa0 (5-6-5): as 0x4975d0 with each level sum taken again
 * with the fixed channel (0x54d5dc, 0x54d5de and 0x54d5e0) and halved before the map is applied.
 * Returns the target address; edx is unchanged. */
uint32_t vertrix_port_pixel16_entry_levels_tint_497ee0(PORT_SIGNATURE);
uint32_t vertrix_port_pixel16_entry_levels_tint_49ffa0(PORT_SIGNATURE);

/* Originals 0x499bc0 (5-5-5) and 0x4a1c80 (5-6-5): as 0x4975d0 with the source's entry replaced by
 * the dword picked as 0x498470 picks it (the index stored at 0x54d5e4, the dword at 0x54d5d4); the
 * map stays the one of the source's own entry. Returns the target address; edx is unchanged. */
uint32_t vertrix_port_pixel16_fixed_entry_levels_499bc0(PORT_SIGNATURE);
uint32_t vertrix_port_pixel16_fixed_entry_levels_4a1c80(PORT_SIGNATURE);

/* Original 0x48dda0: the target becomes the source less the target, each channel stopping at 0
 * (the raw difference at 0x54d624). Returns the target address. */
uint32_t vertrix_port_blend_subtract_from(PORT_SIGNATURE);

/* Original 0x48ddf0: the target becomes the inverted source (low 24 bits). Returns the colour. */
uint32_t vertrix_port_blend_invert(PORT_SIGNATURE);

/* Original 0x48de10: the target is inverted (low 24 bits). Returns the target address. */
uint32_t vertrix_port_blend_invert_target(PORT_SIGNATURE);

/* Original 0x48d890: the target becomes the source halved (masked to 0x7f7f7f) plus the colour at
 * 0x54d5ec. Returns the colour. */
uint32_t vertrix_port_blend_half_plus(PORT_SIGNATURE);

/* Original 0x48d9a0: the target becomes that colour, then the target is remapped. Returns the
 * target address. */
uint32_t vertrix_port_blend_half_plus_remap(PORT_SIGNATURE);

/* Original 0x48df10: the source's colour entry (stored at 0x54d5d4) remapped through the map the
 * target's entry selects (stored at 0x54d5d0). Returns the target address. */
uint32_t vertrix_port_blend_target_cross_remap(PORT_SIGNATURE);

/* Original 0x48e0c0: the target becomes the average of itself and the remapped source (kept at
 * 0x5bc018). Returns the target address. */
uint32_t vertrix_port_blend_remap_average(PORT_SIGNATURE);

/* Original 0x48e370: the target becomes the remapped source (kept at 0x5bc018) less the target,
 * each channel stopping at 0. Returns the target address. */
uint32_t vertrix_port_blend_remap_subtract_from(PORT_SIGNATURE);

/* Original 0x48e460: the target becomes the remapped source (kept at 0x5bc018) inverted (low 24
 * bits). Returns that colour. */
uint32_t vertrix_port_blend_remap_invert(PORT_SIGNATURE);

/* Original 0x48e520: the target becomes its remapped colour (kept at 0x5bc018) inverted (low 24
 * bits). Returns the target address. */
uint32_t vertrix_port_blend_target_remap_invert(PORT_SIGNATURE);

/* Original 0x48e5f0: the target becomes the fixed channels remapped through the map numbered by
 * the mean (rounded down) of the source's and the target's entry bytes (stored at 0x54d5d0).
 * Returns the target address. */
uint32_t vertrix_port_blend_mean_map_tint(PORT_SIGNATURE);

/* Original 0x48e6c0: the target becomes the sum of the source's and its own quarters (masked to
 * 0x3f3f3f) and the colour at 0x54d5ec. Returns the target address. */
uint32_t vertrix_port_blend_quarters_plus(PORT_SIGNATURE);

/* Original 0x48e700: the target becomes the map of the source's colour entry (the entry stored at
 * 0x54d5d4, the map at 0x54d5d0) applied to the means of that entry's bytes 3, 2 and 1 and the
 * target's entry's (stored at 0x54d5d8), each meaned again with the fixed channel. Returns the
 * target address. */
uint32_t vertrix_port_blend_entry_mean_tint(PORT_SIGNATURE);

/* Original 0x48e9d0: saturating add to the target of the source halved plus the colour at 0x54d5ec
 * (kept at 0x5bc018). Returns the target address. */
uint32_t vertrix_port_blend_half_plus_add(PORT_SIGNATURE);

/* Original 0x48eb40: saturating subtract from the target of the source remapped through fixed
 * channels (kept at 0x5bc018). Returns the target address. */
uint32_t vertrix_port_blend_tint_subtract(PORT_SIGNATURE);

/* Original 0x48ec10: saturating subtract from the target of the source halved plus the colour at
 * 0x54d5ec (kept at 0x5bc018). Returns the target address. */
uint32_t vertrix_port_blend_half_plus_subtract(PORT_SIGNATURE);

/* Original 0x48ed80: the target becomes the source remapped through fixed channels (kept at
 * 0x5bc018) less the target, each channel stopping at 0. Returns the target address. */
uint32_t vertrix_port_blend_tint_subtract_from(PORT_SIGNATURE);

/* Original 0x48ee50: the target becomes the source halved plus the colour at 0x54d5ec (kept at
 * 0x5bc018) less the target, each channel stopping at 0. Returns the target address. */
uint32_t vertrix_port_blend_half_plus_subtract_from(PORT_SIGNATURE);

/* Original 0x48eeb0: the target becomes the source remapped half way to the fixed channels (kept
 * at 0x5bc018) less the target, each channel stopping at 0. Returns the target address. */
uint32_t vertrix_port_blend_half_tint_subtract_from(PORT_SIGNATURE);

/* Original 0x48efc0: the target becomes the inverted source (low 24 bits kept at 0x5bc018)
 * remapped through fixed channels. Returns the target address. */
uint32_t vertrix_port_blend_invert_tint(PORT_SIGNATURE);

/* Original 0x48f070: the target becomes the inverted source (low 24 bits, kept at 0x5bc018) halved
 * plus the colour at 0x54d5ec. Returns the colour. */
uint32_t vertrix_port_blend_invert_half_plus(PORT_SIGNATURE);

/* Original 0x48f0a0: the target becomes the inverted source (low 24 bits kept at 0x5bc018)
 * remapped half way to the fixed channels. Returns the colour. */
uint32_t vertrix_port_blend_invert_half_tint(PORT_SIGNATURE);

/* Original 0x48f190: the target becomes its inverted colour (low 24 bits kept at 0x5bc018)
 * remapped through fixed channels. Returns the colour. */
uint32_t vertrix_port_blend_invert_target_tint(PORT_SIGNATURE);

/* Original 0x48f230: the target becomes its inverted colour (low 24 bits, kept at 0x5bc018) halved
 * plus the colour at 0x54d5ec. Returns the target address. */
uint32_t vertrix_port_blend_invert_target_half_plus(PORT_SIGNATURE);

/* Original 0x48f260: the target becomes its inverted colour (low 24 bits kept at 0x5bc018)
 * remapped half way to the fixed channels. Returns the colour. */
uint32_t vertrix_port_blend_invert_target_half_tint(PORT_SIGNATURE);

/* Original 0x48f360: the target becomes the fixed channels remapped through the map the source's
 * entry selects (stored at 0x54d5d0); the target's entry is stored at 0x54d5d4. Returns the target
 * address. */
uint32_t vertrix_port_blend_source_tint(PORT_SIGNATURE);

/* Original 0x48f430: the target's colour entry (stored at 0x54d5d4) remapped through the map the
 * source's entry selects (stored at 0x54d5d0), kept at 0x5bc018, then halved plus the colour at
 * 0x54d5ec. Returns the target address. */
uint32_t vertrix_port_blend_cross_remap_half_plus(PORT_SIGNATURE);

/* Original 0x48f520: the target's colour entry (stored at 0x54d5d4) remapped half way to the fixed
 * channels through the map the source's entry selects (stored at 0x54d5d0). Returns the target
 * address. */
uint32_t vertrix_port_blend_cross_half_tint(PORT_SIGNATURE);

/* Original 0x48f620: as 0x48f360 with the map from the target and the entry from the source.
 * Returns the target address. */
uint32_t vertrix_port_blend_target_tint(PORT_SIGNATURE);

/* Original 0x48f6f0: as 0x48f430 with the map from the target and the entry from the source.
 * Returns the target address. */
uint32_t vertrix_port_blend_target_cross_remap_half_plus(PORT_SIGNATURE);

/* Original 0x48f800: as 0x48f520 with the map from the target and the entry from the source.
 * Returns the target address. */
uint32_t vertrix_port_blend_target_cross_half_tint(PORT_SIGNATURE);

/* Original 0x48f910: the target becomes the colour of 0x48e6c0, then the target is remapped.
 * Returns the target address. */
uint32_t vertrix_port_blend_quarters_plus_remap(PORT_SIGNATURE);

/* Original 0x48f9f0: saturating add to the target of the source halved plus the colour at 0x54d5ec
 * and remapped (kept at 0x5bc018). Returns the target address. */
uint32_t vertrix_port_blend_half_plus_remap_add(PORT_SIGNATURE);

/* Original 0x48faf0: saturating subtract of that colour from the target. Returns the target
 * address. */
uint32_t vertrix_port_blend_half_plus_remap_subtract(PORT_SIGNATURE);

/* Original 0x48fbe0: the target becomes that colour less the target, each channel stopping at 0.
 * Returns the target address. */
uint32_t vertrix_port_blend_half_plus_remap_subtract_from(PORT_SIGNATURE);

/* Original 0x48fcd0: the target becomes the inverted source (low 24 bits) halved plus the colour
 * at 0x54d5ec (kept at 0x5bc018) and remapped. Returns the colour. */
uint32_t vertrix_port_blend_invert_half_plus_remap(PORT_SIGNATURE);

/* Original 0x48fdb0: the target becomes its inverted colour (low 24 bits) halved plus the colour
 * at 0x54d5ec (kept at 0x5bc018) and remapped. Returns the colour. */
uint32_t vertrix_port_blend_invert_target_half_plus_remap(PORT_SIGNATURE);

/* Original 0x48fe90: the target's colour entry (stored at 0x54d5d4) through the map the source's
 * entry selects (not stored), halved plus the colour at 0x54d5ec (kept at 0x5bc018), then
 * remapped. Returns the target address. */
uint32_t vertrix_port_blend_cross_half_plus_remap(PORT_SIGNATURE);

/* Original 0x490010: the same with the map from the target and the entry from the source. Returns
 * the target address. */
uint32_t vertrix_port_blend_target_cross_half_plus_remap(PORT_SIGNATURE);

/* Original 0x4908c0: each channel of the target becomes half the sum of the source's level (table
 * at [0x55f1f0]), the target's level (table at [0x55f1f4]) and the channel's byte at 0x54d5e8,
 * 0x54d5e9 or 0x54d5ea (the halves or-ed into place). Returns the target address. */
uint32_t vertrix_port_blend_levels_bias(PORT_SIGNATURE);

/* Original 0x490980: the target becomes the map of the source's colour entry (the entry stored at
 * 0x54d5d4, the map at 0x54d5d0) applied to the sums of that entry's bytes 3, 2 and 1 through
 * [0x55f1f0] and the target's entry's (stored at 0x54d5d8) through [0x55f1f4], each meaned with
 * the fixed channel. Returns the target address. */
uint32_t vertrix_port_blend_entry_levels_tint(PORT_SIGNATURE);

/* Original 0x490dc0: the target becomes the source remapped as 0x498470 does. Returns the colour.
 */
uint32_t vertrix_port_blend_paired(PORT_SIGNATURE);

/* Original 0x490e90: the target becomes the colour of 0x498570 (the map the source's entry selects
 * applied to the dword through entry [0x54d5f0] of [0x54cdcc]). Returns the colour. */
uint32_t vertrix_port_blend_fixed_entry(PORT_SIGNATURE);

/* Original 0x490f60: the target becomes the source halved plus the colour at 0x54d5ec (kept at
 * 0x5bc018), remapped as 0x498470 does. Returns the target address. */
uint32_t vertrix_port_blend_half_plus_paired(PORT_SIGNATURE);

/* Original 0x491050: the target becomes the colour of 0x498770 (the source remapped half way to
 * the fixed channels, its map applied again to the dword picked from that colour's entry index).
 * Returns the colour. */
uint32_t vertrix_port_blend_half_tint_fixed(PORT_SIGNATURE);

/* Original 0x4911d0: the target becomes the colour of 0x498910 for the 32-bit target. Returns the
 * target address. */
uint32_t vertrix_port_blend_mean_map_paired(PORT_SIGNATURE);

/* Original 0x4912e0: the target becomes the average of the source and the target (kept at
 * 0x5bc018) remapped as 0x498470 does. Returns the colour. */
uint32_t vertrix_port_blend_average_paired(PORT_SIGNATURE);

/* Original 0x4913e0: the target becomes the colour of 0x498bf0 for the 32-bit target. Returns the
 * target address. */
uint32_t vertrix_port_blend_fixed_entry_mean(PORT_SIGNATURE);

/* Original 0x491530: the target becomes the average of itself and the source remapped as 0x498470
 * does (kept at 0x5bc018). Returns the target address. */
uint32_t vertrix_port_blend_paired_average(PORT_SIGNATURE);

/* Original 0x491720: saturating subtract from the target of the source remapped as 0x498470 does
 * (kept at 0x5bc018). Returns the target address. */
uint32_t vertrix_port_blend_paired_subtract(PORT_SIGNATURE);

/* Original 0x491820: the target becomes the source remapped as 0x498470 does (kept at 0x5bc018)
 * less the target, each channel stopping at 0. Returns the target address. */
uint32_t vertrix_port_blend_paired_subtract_from(PORT_SIGNATURE);

/* Original 0x491920: the target becomes the source remapped as 0x498470 does (kept at 0x5bc018)
 * inverted (low 24 bits). Returns that colour. */
uint32_t vertrix_port_blend_paired_invert(PORT_SIGNATURE);

/* Original 0x491a00: the target becomes its colour remapped as 0x498470 does (kept at 0x5bc018)
 * inverted (low 24 bits). Returns the target address. */
uint32_t vertrix_port_blend_target_paired_invert(PORT_SIGNATURE);

/* Original 0x491af0: the target becomes the map the source's entry selects (stored at 0x54d5d0)
 * applied to the dword picked as 0x498470 picks it from the target's entry index (stored at
 * 0x54d5d4). Returns the target address. */
uint32_t vertrix_port_blend_paired_cross(PORT_SIGNATURE);

/* Original 0x491be0: the same with the map from the target and the dword from the source. Returns
 * the target address. */
uint32_t vertrix_port_blend_target_paired_cross(PORT_SIGNATURE);

/* Original 0x491ce0: the target becomes the colour of 0x499860 for the 32-bit target. Returns the
 * target address. */
uint32_t vertrix_port_blend_shade_paired(PORT_SIGNATURE);

/* Original 0x491e10: the target becomes the two-table sum of 0x4902a0, then that colour remapped
 * as 0x498470 does. Returns the target address. */
uint32_t vertrix_port_blend_levels_paired(PORT_SIGNATURE);

/* Original 0x491f70: the target becomes the colour of 0x499bc0 for the 32-bit target. Returns the
 * target address. */
uint32_t vertrix_port_blend_fixed_entry_levels(PORT_SIGNATURE);

/* Original 0x492120: the target becomes the two-table sum of the source remapped as 0x498470 does
 * (kept at 0x5bc018) and itself. Returns the target address. */
uint32_t vertrix_port_blend_paired_levels(PORT_SIGNATURE);

/* Original 0x492a70: (eax = row routine): draw an image's rows from the last up, with sampled
 * source rows. The row index 0x5bb7d4 moves on by the row count (the high word of 0x5bb750) less
 * two, the source 0x5bb764 by the word at 0x5bb7e0 times 0x5bb7c0 pixels, the target row 0x5bb770
 * by the stride 0x5bb7c4 and the mask row 0x5bb7e8 by the mask stride (high word of 0x5bb742) for
 * each row but one. For each of the 16-bit count at 0x5bb750 rows, from the row starts at 0x5bb7ec
 * (0x5bbfec the current one), the pixel count 0x5bc016 is the width less the row's start, the
 * source row 0x5bb76c is the source plus four times the next byte of the list at 0x5bb7d8,
 * 0x5bb7dc becomes the row index, the target pixel and mask are set, the target row moves four
 * bytes and the mask one, and the routine is called (eax the mask, edx the target, ecx the
 * source); the source becomes the source row after it. Returns the last source row; edx is
 * unchanged. */
uint32_t vertrix_port_render_sampled_rows(PORT_SIGNATURE);

/* Original 0x49a780: the same for 16-bit targets (the pixel and row at 0x5bb780 and 0x5bb784, two
 * bytes on). */
uint32_t vertrix_port_render_sampled_rows_49a780(PORT_SIGNATURE);

/* Original 0x4a2840: the same code as 0x49a780. */
uint32_t vertrix_port_render_sampled_rows_4a2840(PORT_SIGNATURE);

/* Original 0x4925d0: 0x492770 for a source with an alpha byte: the pixel operation runs (eax the
 * alpha) only where the source's top byte is not 0, and in the row start's part only where the
 * mask bit is clear too. Returns the eax left at the end; edx is unchanged. */
uint32_t vertrix_port_render_keyed_mask_row_back(PORT_SIGNATURE);

/* Original 0x49a2f0: the same for the 16-bit target pixel at 0x5bb780. */
uint32_t vertrix_port_render_keyed_mask_row_back_49a2f0(PORT_SIGNATURE);

/* Original 0x4a23b0: the same for the 16-bit target pixel at 0x5bb780. */
uint32_t vertrix_port_render_keyed_mask_row_back_4a23b0(PORT_SIGNATURE);

/* Original 0x49a020: 0x4922f0 for the 16-bit target pixel at 0x5bb780. */
uint32_t vertrix_port_render_mask_alpha_row_49a020(PORT_SIGNATURE);

/* Original 0x4a20e0: the same code as 0x49a020. */
uint32_t vertrix_port_render_mask_alpha_row_4a20e0(PORT_SIGNATURE);

/* The rectangle fills (32-bit 0x492b90, 0x492cc0, 0x492e40, 0x492f90; 16-bit 0x49a8a0, 0x49aa40,
 * 0x49abb0, 0x49aca0, 0x49ae50 in 5-5-5 and 0x4a2960, 0x4a2af0, 0x4a2c60, 0x4a2d50, 0x4a2ef0 in
 * 5-6-5): remap, tint, half plus, half tint and half plus remap of each pixel in place. */
uint32_t vertrix_port_rectangle_remap32_492b90(PORT_SIGNATURE);
uint32_t vertrix_port_rectangle_tint32_492cc0(PORT_SIGNATURE);
uint32_t vertrix_port_rectangle_half_tint32_492e40(PORT_SIGNATURE);
uint32_t vertrix_port_rectangle_half_plus_remap32_492f90(PORT_SIGNATURE);
uint32_t vertrix_port_rectangle_remap16_49a8a0(PORT_SIGNATURE);
uint32_t vertrix_port_rectangle_remap16_4a2960(PORT_SIGNATURE);
uint32_t vertrix_port_rectangle_tint16_49aa40(PORT_SIGNATURE);
uint32_t vertrix_port_rectangle_tint16_4a2af0(PORT_SIGNATURE);
uint32_t vertrix_port_rectangle_half_plus16_49abb0(PORT_SIGNATURE);
uint32_t vertrix_port_rectangle_half_plus16_4a2c60(PORT_SIGNATURE);
uint32_t vertrix_port_rectangle_half_tint16_49aca0(PORT_SIGNATURE);
uint32_t vertrix_port_rectangle_half_tint16_4a2d50(PORT_SIGNATURE);
uint32_t vertrix_port_rectangle_half_plus_remap16_49ae50(PORT_SIGNATURE);
uint32_t vertrix_port_rectangle_half_plus_remap16_4a2ef0(PORT_SIGNATURE);

/* The 3-3-2 copies of the narrow pixel operations (0x4a3540 to 0x4a9ba0), one for each 5-5-5
 * one above. */
uint32_t vertrix_port_pixel8_copy_4a3540(PORT_SIGNATURE);
uint32_t vertrix_port_pixel8_remap_4a3580(PORT_SIGNATURE);
uint32_t vertrix_port_pixel8_tint_4a3660(PORT_SIGNATURE);
uint32_t vertrix_port_pixel8_half_plus_4a3720(PORT_SIGNATURE);
uint32_t vertrix_port_pixel8_half_tint_4a3770(PORT_SIGNATURE);
uint32_t vertrix_port_pixel8_half_plus_remap_4a3880(PORT_SIGNATURE);
uint32_t vertrix_port_pixel8_mean_map_remap_4a3970(PORT_SIGNATURE);
uint32_t vertrix_port_pixel8_average_4a3ac0(PORT_SIGNATURE);
uint32_t vertrix_port_pixel8_entry_mean_4a3b50(PORT_SIGNATURE);
uint32_t vertrix_port_pixel8_average_4a3ce0(PORT_SIGNATURE);
uint32_t vertrix_port_pixel8_add_4a3d70(PORT_SIGNATURE);
uint32_t vertrix_port_pixel8_subtract_4a3e20(PORT_SIGNATURE);
uint32_t vertrix_port_pixel8_subtract_from_4a3ed0(PORT_SIGNATURE);
uint32_t vertrix_port_pixel8_invert_4a3f80(PORT_SIGNATURE);
uint32_t vertrix_port_pixel8_invert_target_4a3fd0(PORT_SIGNATURE);
uint32_t vertrix_port_pixel8_cross_remap_4a4040(PORT_SIGNATURE);
uint32_t vertrix_port_pixel8_target_cross_remap_4a4170(PORT_SIGNATURE);
uint32_t vertrix_port_pixel8_average_remap_4a42b0(PORT_SIGNATURE);
uint32_t vertrix_port_pixel8_remap_average_4a43e0(PORT_SIGNATURE);
uint32_t vertrix_port_pixel8_remap_add_4a4520(PORT_SIGNATURE);
uint32_t vertrix_port_pixel8_remap_subtract_4a4660(PORT_SIGNATURE);
uint32_t vertrix_port_pixel8_remap_subtract_from_4a47a0(PORT_SIGNATURE);
uint32_t vertrix_port_pixel8_remap_invert_4a48e0(PORT_SIGNATURE);
uint32_t vertrix_port_pixel8_target_remap_invert_4a49e0(PORT_SIGNATURE);
uint32_t vertrix_port_pixel8_mean_map_tint_4a4b10(PORT_SIGNATURE);
uint32_t vertrix_port_pixel8_quarters_plus_4a4c40(PORT_SIGNATURE);
uint32_t vertrix_port_pixel8_entry_mean_tint_4a4cd0(PORT_SIGNATURE);
uint32_t vertrix_port_pixel8_tint_average_4a4e80(PORT_SIGNATURE);
uint32_t vertrix_port_pixel8_tint_add_4a4f90(PORT_SIGNATURE);
uint32_t vertrix_port_pixel8_half_plus_add_4a50c0(PORT_SIGNATURE);
uint32_t vertrix_port_pixel8_half_tint_add_4a5180(PORT_SIGNATURE);
uint32_t vertrix_port_pixel8_tint_subtract_4a5300(PORT_SIGNATURE);
uint32_t vertrix_port_pixel8_half_plus_subtract_4a5420(PORT_SIGNATURE);
uint32_t vertrix_port_pixel8_half_tint_subtract_4a54e0(PORT_SIGNATURE);
uint32_t vertrix_port_pixel8_tint_subtract_from_4a5660(PORT_SIGNATURE);
uint32_t vertrix_port_pixel8_half_plus_subtract_from_4a5780(PORT_SIGNATURE);
uint32_t vertrix_port_pixel8_half_tint_subtract_from_4a5840(PORT_SIGNATURE);
uint32_t vertrix_port_pixel8_invert_tint_4a59c0(PORT_SIGNATURE);
uint32_t vertrix_port_pixel8_invert_half_plus_4a5aa0(PORT_SIGNATURE);
uint32_t vertrix_port_pixel8_invert_half_tint_4a5b00(PORT_SIGNATURE);
uint32_t vertrix_port_pixel8_invert_target_tint_4a5c20(PORT_SIGNATURE);
uint32_t vertrix_port_pixel8_invert_target_half_plus_4a5d20(PORT_SIGNATURE);
uint32_t vertrix_port_pixel8_invert_target_half_tint_4a5db0(PORT_SIGNATURE);
uint32_t vertrix_port_pixel8_source_tint_4a5ef0(PORT_SIGNATURE);
uint32_t vertrix_port_pixel8_cross_remap_half_plus_4a6020(PORT_SIGNATURE);
uint32_t vertrix_port_pixel8_cross_half_tint_4a6170(PORT_SIGNATURE);
uint32_t vertrix_port_pixel8_target_tint_4a62d0(PORT_SIGNATURE);
uint32_t vertrix_port_pixel8_target_cross_remap_half_plus_4a6400(PORT_SIGNATURE);
uint32_t vertrix_port_pixel8_target_cross_half_tint_4a6550(PORT_SIGNATURE);
uint32_t vertrix_port_pixel8_quarters_plus_remap_4a66b0(PORT_SIGNATURE);
uint32_t vertrix_port_pixel8_half_plus_remap_add_4a67f0(PORT_SIGNATURE);
uint32_t vertrix_port_pixel8_half_plus_remap_subtract_4a6950(PORT_SIGNATURE);
uint32_t vertrix_port_pixel8_half_plus_remap_subtract_from_4a6aa0(PORT_SIGNATURE);
uint32_t vertrix_port_pixel8_invert_half_plus_remap_4a6bf0(PORT_SIGNATURE);
uint32_t vertrix_port_pixel8_invert_target_half_plus_remap_4a6d10(PORT_SIGNATURE);
uint32_t vertrix_port_pixel8_cross_half_plus_remap_4a6e60(PORT_SIGNATURE);
uint32_t vertrix_port_pixel8_target_cross_half_plus_remap_4a7050(PORT_SIGNATURE);
uint32_t vertrix_port_pixel8_shade_4a7240(PORT_SIGNATURE);
uint32_t vertrix_port_blend_levels8_4a73b0(PORT_SIGNATURE);
uint32_t vertrix_port_pixel8_entry_levels_4a74b0(PORT_SIGNATURE);
uint32_t vertrix_port_blend_levels8_4a7690(PORT_SIGNATURE);
uint32_t vertrix_port_pixel8_levels_remap_4a7790(PORT_SIGNATURE);
uint32_t vertrix_port_pixel8_remap_levels_4a7940(PORT_SIGNATURE);
uint32_t vertrix_port_pixel8_shade_tint_4a7af0(PORT_SIGNATURE);
uint32_t vertrix_port_pixel8_levels_bias_4a7c30(PORT_SIGNATURE);
uint32_t vertrix_port_pixel8_entry_levels_tint_4a7d60(PORT_SIGNATURE);
uint32_t vertrix_port_pixel8_tint_levels_4a7f60(PORT_SIGNATURE);
uint32_t vertrix_port_pixel8_levels_bias_remap_4a80e0(PORT_SIGNATURE);
uint32_t vertrix_port_pixel8_paired_entry_4a82c0(PORT_SIGNATURE);
uint32_t vertrix_port_pixel8_fixed_entry_4a83c0(PORT_SIGNATURE);
uint32_t vertrix_port_pixel8_half_plus_paired_4a84b0(PORT_SIGNATURE);
uint32_t vertrix_port_pixel8_half_tint_fixed_4a85c0(PORT_SIGNATURE);
uint32_t vertrix_port_pixel8_mean_map_paired_4a8760(PORT_SIGNATURE);
uint32_t vertrix_port_pixel8_average_paired_4a88d0(PORT_SIGNATURE);
uint32_t vertrix_port_pixel8_fixed_entry_mean_4a8a30(PORT_SIGNATURE);
uint32_t vertrix_port_pixel8_paired_average_4a8be0(PORT_SIGNATURE);
uint32_t vertrix_port_pixel8_paired_add_4a8d40(PORT_SIGNATURE);
uint32_t vertrix_port_pixel8_paired_subtract_4a8ea0(PORT_SIGNATURE);
uint32_t vertrix_port_pixel8_paired_subtract_from_4a8ff0(PORT_SIGNATURE);
uint32_t vertrix_port_pixel8_paired_invert_4a9140(PORT_SIGNATURE);
uint32_t vertrix_port_pixel8_target_paired_invert_4a9250(PORT_SIGNATURE);
uint32_t vertrix_port_pixel8_paired_cross_4a9390(PORT_SIGNATURE);
uint32_t vertrix_port_pixel8_target_paired_cross_4a94f0(PORT_SIGNATURE);
uint32_t vertrix_port_pixel8_shade_paired_4a9640(PORT_SIGNATURE);
uint32_t vertrix_port_pixel8_levels_paired_4a97d0(PORT_SIGNATURE);
uint32_t vertrix_port_pixel8_fixed_entry_levels_4a99a0(PORT_SIGNATURE);
uint32_t vertrix_port_pixel8_paired_levels_4a9ba0(PORT_SIGNATURE);

/* The 8-bit row routines and rectangle fills, with the target pointer at 0x5bb778 (0x4a9d70
 * to 0x4aabe0). */
uint32_t vertrix_port_render_keyed_row8_4a9d70(PORT_SIGNATURE);
uint32_t vertrix_port_render_mask_alpha_row8_4a9de0(PORT_SIGNATURE);
uint32_t vertrix_port_render_row8_4a9ee0(PORT_SIGNATURE);
uint32_t vertrix_port_render_sampled_row8_4aa030(PORT_SIGNATURE);
uint32_t vertrix_port_render_keyed_mask_row_back8_4aa0b0(PORT_SIGNATURE);
uint32_t vertrix_port_render_image_rows8_4aa450(PORT_SIGNATURE);
uint32_t vertrix_port_render_sampled_rows8_4aa540(PORT_SIGNATURE);
uint32_t vertrix_port_rectangle_remap8_4aa660(PORT_SIGNATURE);
uint32_t vertrix_port_rectangle_tint8_4aa7f0(PORT_SIGNATURE);
uint32_t vertrix_port_rectangle_half_plus8_4aa950(PORT_SIGNATURE);
uint32_t vertrix_port_rectangle_half_tint8_4aaa40(PORT_SIGNATURE);
uint32_t vertrix_port_rectangle_half_plus_remap8_4aabe0(PORT_SIGNATURE);

/* The masked alpha blits by columns, bottom row up: 32-bit 0x4930c0, 5-5-5 0x49b000, 5-6-5 0x4a30a0
 * and 3-3-2 0x4aad90. */
uint32_t vertrix_port_alpha_columns32_4930c0(PORT_SIGNATURE);
uint32_t vertrix_port_alpha_columns16_49b000(PORT_SIGNATURE);
uint32_t vertrix_port_alpha_columns16_4a30a0(PORT_SIGNATURE);
uint32_t vertrix_port_alpha_columns8_4aad90(PORT_SIGNATURE);

/* The image blits: 32-bit alpha 0x4ab380; keyed, copy and alpha in 5-5-5 (0x4ab4a0), 5-6-5
 * (0x4ab790) and 3-3-2 (0x4aba80). */
uint32_t vertrix_port_image_alpha32_4ab380(PORT_SIGNATURE);
uint32_t vertrix_port_image_keyed16_4ab4a0(PORT_SIGNATURE);
uint32_t vertrix_port_image_copy16_4ab540(PORT_SIGNATURE);
uint32_t vertrix_port_image_alpha16_4ab5e0(PORT_SIGNATURE);
uint32_t vertrix_port_image_keyed16_4ab790(PORT_SIGNATURE);
uint32_t vertrix_port_image_copy16_4ab830(PORT_SIGNATURE);
uint32_t vertrix_port_image_alpha16_4ab8d0(PORT_SIGNATURE);
uint32_t vertrix_port_image_keyed8_4aba80(PORT_SIGNATURE);
uint32_t vertrix_port_image_copy8_4abb30(PORT_SIGNATURE);
uint32_t vertrix_port_image_alpha8_4abbd0(PORT_SIGNATURE);

#endif
