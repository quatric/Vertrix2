#ifndef VERTRIX_RENDER_DISPATCH_H
#define VERTRIX_RENDER_DISPATCH_H
#include "surface.h"
#include <stdint.h>
/* Original 0x4af2a0: first matching required/allowed flag rule, or 92. */
uint32_t vertrix_render_rule(uint32_t flags);
/* Original 0x4b1fb8..0x4b2008: original-address evidence identifier.
 * Zero means no selected kernel. Addresses must never be called by Wii code. */
uint32_t vertrix_render_kernel_address(uint32_t flags, uint8_t target_format);
/* Inputs correspond to original renderer globals; names do not infer effect
 * meanings that have not yet been recovered. Byte equality tests are exact. */
typedef struct
{
    uint8_t flag_73a;
    uint8_t flag_739;
    uint8_t effect_00d;
    uint8_t amount_00e;
    uint8_t format_000;
    uint8_t format_730;
    uint8_t transform_00c;
    uint16_t word_002;
} VertrixRenderFlagState;
/* Original 0x4af370; mode == 1 selects the direct path. */
uint32_t vertrix_render_flags(VertrixRenderFlagState state, uint32_t mode);

/* Direct rule-zero kernels: format 4 copies all bits; 2 produces RGB565,
 * 1 RGB555, 0 RGB332. Source channels are bits 16..23, 8..15, 0..7. */
uint32_t vertrix_render_direct_pixel(uint32_t source, uint8_t target_format);
int vertrix_render_direct_write(VertrixSurface *target, uint8_t target_format, uint32_t x,
                                uint32_t y, uint32_t source);

/* Original 32-bit effect kernels 1,3..8 at amount 50; no palette transform.
 * Effects 1/3 half-blend, 4 adds, 5 destination-source, 6 source-destination,
 * 7 inverts source, 8 inverts destination. Unsupported effects preserve output. */
int vertrix_render_effect_pixel(uint32_t source, uint32_t destination, uint8_t effect,
                                uint32_t *output);

/* Original 0x4af530, 0x4af2e0 and 0x4af340: traversal flags and table indices.
 * Sentinel index 8/4 denotes unsupported combinations. */
uint32_t vertrix_render_traversal_flags(uint8_t flag_fff, uint8_t scale_738, uint8_t flag_ff0);
uint32_t vertrix_render_traversal_index(uint32_t flags);
uint32_t vertrix_render_traversal_group(uint32_t flags);
typedef struct
{
    uint32_t row_address;
    uint32_t image_address;
} VertrixRenderTraversal;
/* Original 0x4af707..0x4af77d and tables 0x4ff684/0x4ff6c4.
 * Addresses identify recovered behavior; never call them as native pointers.
 * Unsupported target formats preserve output. */
int vertrix_render_traversal(uint8_t flag_fff, uint8_t scale_738, uint8_t flag_ff0,
                             uint8_t target_format, VertrixRenderTraversal *output);
typedef struct
{
    uint32_t operation_address;
    uint32_t prepare;
} VertrixRenderOperation;
/* Original 0x4af786..0x4af86d after valid kernel/row/image binding.
 * Selects fast copy, alpha override or prepared image traversal. Addresses
 * remain evidence identifiers. Invalid inputs preserve output. */
int vertrix_render_operation(uint32_t rule, uint32_t traversal_index, uint32_t traversal_group,
                             uint8_t target_format, uint32_t alpha_override,
                             VertrixRenderOperation *output);

/* Original pixel-rendering gate 0x4af560..0x4af6ad. Border handling remains
 * separate even when pixel drawing is disabled. */
int vertrix_render_pixels_enabled(uint32_t pixel_resource, uint8_t scale,
                                  VertrixRenderFlagState state);

/* Original weighted blend 0x4902a0; valid source percentages 0..100.
 * Both operands truncate separately, then channels are packed with OR. */
int vertrix_render_weighted_pixel(uint32_t source, uint32_t destination, uint8_t amount,
                                  uint32_t *output);

#endif
