#ifndef VERTRIX_RENDER_GEOMETRY_H
#define VERTRIX_RENDER_GEOMETRY_H

#include "surface.h"
#include <stdint.h>

typedef struct
{
    int16_t left;
    int16_t right;
    int16_t top;
    int16_t bottom;
} VertrixBoardClip;

/* Original 0x42ff10: inclusive 120x312 board clipping bounds. */
VertrixBoardClip vertrix_board_clip(int16_t origin_x, int16_t origin_y);
/* Original positioning phase 0x430930..0x4309f9, occupied blocks with mode 16.
 * Other modes subsequently center the resource using its dimensions.
 * Cell indices must be column 0..4, row 0..12. */
int vertrix_board_cell_position(int16_t origin_x, int16_t origin_y, uint32_t column, uint32_t row,
                                int8_t offset_x, int8_t offset_y, int16_t *x, int16_t *y);

/* Original 0x4310ba..0x4310ee: center a measured resource in a 24x24 cell.
 * Dimensions come from the separate original resource measurement routine.
 * Subtraction and logical shift retain x86 wrapping; results wrap to words. */
int vertrix_board_cell_center(int16_t cell_x, int16_t cell_y, int32_t width, int32_t height,
                              int16_t *x, int16_t *y);

/* Original 0x4b14c0: resolved source dimensions and scale modes 0..16.
 * The caller resolves descriptor/fallback dimensions and global mode override.
 * Outputs signed-word dimensions, using the original remainder lookup table. */
int vertrix_resource_measure(uint16_t width, uint16_t height, uint8_t mode, int32_t *measured_width,
                             int32_t *measured_height);

/* Descriptor dimensions correspond to offsets +4/+8. NULL selects object fallback.
 * Nonzero screen_override selects mode 16 when screen_unscaled is nonzero,
 * otherwise screen_mode, matching original object +0x91 and screen +0x220/+0x221. */
typedef struct
{
    uint16_t width;
    uint16_t height;
} VertrixResourceDimensions;

int vertrix_resource_measure_state(const VertrixResourceDimensions *descriptor,
                                   VertrixResourceDimensions fallback, uint8_t object_mode,
                                   uint8_t screen_override, uint8_t screen_unscaled,
                                   uint8_t screen_mode, int32_t *width, int32_t *height);

/* Original fragment 0x4b15e0: measured bounds subtract the descriptor anchor from position.
 * Anchor scaling uses signed measured dimensions, truncation toward zero and
 * signed-word wrapping. Non-16 modes require nonzero source dimensions. */
int vertrix_resource_bounds(uint16_t source_width, uint16_t source_height, int16_t anchor_x,
                            int16_t anchor_y, uint8_t mode, int16_t position_x, int16_t position_y,
                            int32_t *x, int32_t *y, int32_t *width, int32_t *height);

typedef struct
{
    VertrixBoardClip bounds;
    uint16_t width;
    uint16_t height;
    uint32_t source_offset;
    uint8_t clipped;
} VertrixSpriteClip;

/* Original unscaled clipping phase 0x4b1ae9..0x4b1c6f.
 * Coordinates and inclusive endpoints retain signed-word wrapping.
 * Empty/offscreen sprites return zero and preserve the output. */
int vertrix_sprite_clip(int16_t x, int16_t y, uint16_t width, uint16_t height,
                        VertrixBoardClip clip, VertrixSpriteClip *output);

/* Original fragment 0x4b1a99..0x4b1f27: modes 0/1 use target dimensions, 2 bypasses
 * clipping, 3 uses object bounds, remaining byte values retain cached bounds. */
int vertrix_sprite_clip_mode(int16_t x, int16_t y, uint16_t width, uint16_t height, uint8_t mode,
                             uint16_t target_width, uint16_t target_height,
                             VertrixBoardClip object_clip, VertrixBoardClip cached_clip,
                             VertrixSpriteClip *output);

/* Compose recovered unscaled clipping with 32-bit rectangle traversal.
 * Returns 1 drawn, 0 clipped out, -1 invalid storage/unsupported dimensions.
 * transparent 0 copies, 1 blends premultiplied alpha, 2 tests nonzero alpha. */
int vertrix_sprite_draw32(const VertrixSurface *source, VertrixSurface *target, int16_t x,
                          int16_t y, uint8_t clip_mode, VertrixBoardClip object_clip,
                          VertrixBoardClip cached_clip, int transparent);

/* Original initializer 0x4b9050 and table selection 0x4ae974..0x4ae991.
 * Read modes 1..15, positions 0..1023. Invalid ranges preserve output. */
int vertrix_render_scale_advances(uint8_t mode, uint32_t start, uint32_t count, uint8_t *output);

/* Original 0x4ae99f..0x4aea50: consume advance entries for clipped rows/columns
 * and add their source-pixel displacement to the existing wrapping offset. */
int vertrix_render_scale_clip_offset(uint8_t mode, uint16_t source_width, uint16_t skipped_columns,
                                     uint16_t skipped_rows, uint32_t initial_offset,
                                     uint32_t *output);

/* Recovered opaque scaled phases, modes 1..15, packed 32-bit source.
 * Returns 1 drawn, 0 clipped out/zero measured size, -1 invalid storage/range. */
int vertrix_sprite_draw_scaled32(const VertrixSurface *source, VertrixSurface *target, int16_t x,
                                 int16_t y, uint8_t scale, uint8_t clip_mode,
                                 VertrixBoardClip object_clip, VertrixBoardClip cached_clip);

/* Same recovered scaled geometry, selecting original nonzero-alpha traversal. */
int vertrix_sprite_draw_scaled_binary32(const VertrixSurface *source, VertrixSurface *target,
                                        int16_t x, int16_t y, uint8_t scale, uint8_t clip_mode,
                                        VertrixBoardClip object_clip, VertrixBoardClip cached_clip);

/* Recovered clipped scaled geometry plus amount-50 effects 1,3..8.
 * binary selects zero-alpha skipping; return values match other scaled APIs. */
int vertrix_sprite_draw_scaled_effect32(const VertrixSurface *source, VertrixSurface *target,
                                        int16_t x, int16_t y, uint8_t scale, uint8_t clip_mode,
                                        VertrixBoardClip object_clip, VertrixBoardClip cached_clip,
                                        uint8_t effect, int binary);

/* Recovered clipped scaled geometry with weighted blend percentages 0..100. */
int vertrix_sprite_draw_scaled_weighted32(const VertrixSurface *source, VertrixSurface *target,
                                          int16_t x, int16_t y, uint8_t scale, uint8_t clip_mode,
                                          VertrixBoardClip object_clip,
                                          VertrixBoardClip cached_clip, uint8_t amount, int binary);

typedef struct
{
    uint32_t source_address;
    uint32_t source_width;
    int32_t target_width;
    int32_t padding_pixels;
    uint32_t target_stride;
    uint32_t target_padding;
} VertrixRenderBinding;
/* Original 0x4af0ee..0x4af187. source_address is original-address evidence,
 * never a native pointer; native storage uses bounded VertrixSurface views. */
VertrixRenderBinding vertrix_render_binding(uint32_t source_base, uint32_t source_offset,
                                            uint16_t source_width, uint16_t target_width,
                                            uint16_t visible_width, uint32_t target_stride,
                                            uint32_t extra_padding, uint8_t bytes_per_pixel);

#endif
