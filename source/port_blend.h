#ifndef VERTRIX_PORT_BLEND_H
#define VERTRIX_PORT_BLEND_H
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

/* Original 0x492400: run the pixel operation at [0x5bb72c] for each of the 16-bit count at
 * 0x5bc016 pixels, advancing the source and target addresses by four after each. The count is
 * stored before each call and read back after it (as the low 16 bits of edx for the next call,
 * whose upper bits are the last call's edx); the next call has ecx and ebx the advanced source
 * and target addresses and eax the last call's eax. The count left (0) is stored at the end.
 * Returns the last call's eax (eax unchanged without pixels); edx is unchanged. */
uint32_t vertrix_port_render_row32(PORT_SIGNATURE);

/* Original 0x492280: as 0x492400 for a source with an alpha byte: the pixel operation runs only
 * for the pixels whose top byte is not 0 (eax that byte, edx's low 16 bits the count with the
 * upper bits those of the last target address plus four, ecx the source address). The source
 * address and count are stored before each pixel and at the end. Returns the last pixel's top
 * byte, or the operation's eax when it ran for it (eax unchanged without pixels); edx is
 * unchanged. */
uint32_t vertrix_port_render_keyed_row32(PORT_SIGNATURE);

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

/* Original 0x4922f0: as 0x492460 for a source with an alpha byte: the pixel operation runs only
 * for pixels whose top byte is not 0 (eax that byte). */
uint32_t vertrix_port_render_mask_alpha_row(PORT_SIGNATURE);

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

#endif
