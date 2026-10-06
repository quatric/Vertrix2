#ifndef VERTRIX_IMAGE_H
#define VERTRIX_IMAGE_H

#include "vf.h"

typedef struct
{
    uint32_t width;
    uint32_t height;
    unsigned char *rgba;
} VertrixImage;

/* Decode original 24-bit uncompressed BMP artwork directly from VF.
 * Output must be initialized to zero and empty. Pixel rows are top-down RGBA;
 * alpha is 255 until the separately stored original mask is applied.
 * Returns 0 without changing output on unsupported/truncated input or failure. */
int vertrix_image_bmp(VertrixVf *archive, const char *name, VertrixImage *image);
void vertrix_image_free(VertrixImage *image);
/* Original483ce0 four-byte branch: mirror packed rows without changing
 * descriptor origins or channels. Positive dimensions must fit signed words. */
int vertrix_image_mirror_horizontal(VertrixImage *image);
/* Original0x4799f0 compares the complete little-endian four-byte pixel to key.
 * Matching pixels get alpha0; others alpha255. RGB is preserved. */
int vertrix_image_color_key(VertrixImage *image, uint32_t key);
/* Original0x43f200 missing-mask BMP branch uses the top-left pixel as key.
 * Output must be empty. Reads artwork directly from the original VF. */
int vertrix_image_bmp_keyed(VertrixVf *archive, const char *name, VertrixImage *output);
/* Original font crop482f80/47ce10, four-byte pixels and bordered sheets.
 * Output must be empty; crop must fit within the sheet and be narrower than it.
 * Pixel bytes, including transparent RGB, are copied unchanged. */
int vertrix_image_font_crop(const VertrixImage *sheet, uint32_t x, uint32_t y, uint32_t width,
                            uint32_t height, VertrixImage *output);

/* Original block sheet slicing 0x45f0c0: seven rows, eight 24x24 frames.
 * Native colors 0..4 select sheet rows 1..5; stone 5 -> 0; bomb 6 -> 6.
 * Output must be empty; pixels retain the sheet's already processed channels. */
int vertrix_image_block_frame(const VertrixImage *sheet, uint32_t color, uint32_t frame,
                              VertrixImage *output);

typedef struct
{
    uint32_t width;
    uint32_t height;
    unsigned char *indices;
    unsigned char palette[768];
} VertrixPcx;

/* Original one-plane 8-bit RLE PCX assets. Preserve both palette indices
 * and RGB palette, so original mask semantics can be recovered separately.
 * Initialize output to zero; failures leave it untouched. */
int vertrix_image_pcx(VertrixVf *archive, const char *name, VertrixPcx *image);
void vertrix_pcx_free(VertrixPcx *image);

/* Original binary PCX mask application at 0x4797f0: index zero -> alpha 0,
 * nonzero -> alpha 255, preserving RGB. Dimensions must match exactly. */
int vertrix_image_mask(VertrixImage *image, const VertrixPcx *mask);

/* Original graded path 0x4798b0: nonzero indices add offset with 16-bit
 * wrapping then clamp to 255. RGB becomes channel * alpha / 255.
 * Zero indices stay zero. This mutates RGB and writes the resulting alpha. */
int vertrix_image_mask_graded(VertrixImage *image, const VertrixPcx *mask, int32_t offset);

/* Load original BMP artwork and its binary PCX mask directly from VF.
 * Output must be initialized to zero; failure leaves it unchanged. */
int vertrix_image_bmp_masked(VertrixVf *archive, const char *artwork, const char *mask,
                             VertrixImage *output);

typedef struct
{
    VertrixImage image;
    uint32_t frame_count;
    uint32_t metadata[10]; /* Original 40-byte frame descriptor, decoded LE. */
} VertrixSpriteFrame;

/* Original .spr resources: u16 count, then 48-byte records and raw BGRA.
 * Output must be empty. Descriptor fields are retained for later layout recovery.
 * Supports the uncompressed four-byte format used by all original .spr files. */
int vertrix_image_sprite(VertrixVf *archive, const char *name, uint32_t frame,
                         VertrixSpriteFrame *output);
void vertrix_sprite_free(VertrixSpriteFrame *frame);
/* Original483110 owned four-byte clone. Retain serialized metadata and frame
 * count; pixel ownership uses image.rgba. Output must be zero initialized. */
int vertrix_sprite_clone(const VertrixSpriteFrame *source, VertrixSpriteFrame *output);
/* Compose original487790 clone replacement then4877d0 horizontal mirror.
 * Destination owns its previous storage; source must be a distinct frame.
 * Allocate and validate before replacing destination. Preserve source metadata. */
int vertrix_sprite_replace_mirrored(const VertrixSpriteFrame *source,
                                    VertrixSpriteFrame *destination);
/* Original487790 then4877d0 on a direct owned frame bank. Preserve all other
 * entries. Source/destination indices must differ and fit supplied storage. */
int vertrix_sprite_bank_replace_mirrored(VertrixSpriteFrame *frames, size_t count,
                                         size_t source_index, size_t destination_index);
/* Original45dd52..45de10 default frame substitutions. First source comes
 * from runtime5466c4; other pairs are9->10,11->12,28->29,24->25.
 * Direct owned bank; validate/allocate all replacements before publication. */
int vertrix_sprite_bank_configure_ui(VertrixSpriteFrame *frames, size_t count, size_t first_source);

/* Original 0x483750: zero stored alpha becomes 255; nonzero becomes 0.
 * Apply to decoded raw sprite channels before original color conversion.
 * Preserves RGB; this does not implement the renderer's blending. */
int vertrix_image_binary_alpha(VertrixImage *image);

/* Original 0x483ed0 / 0x481e10, with the fixed BGRA source format.
 * Rearrange RGB bytes using destination mask ordering, preserving alpha.
 * This routine still produces four-byte pixels, including for 16-bit masks.
 * Masks must be nonzero and have distinct least-significant bit positions. */
int vertrix_image_color_order(VertrixImage *image, const uint32_t masks[3]);

/* Direct VF sprite loading with the original alpha and color processing.
 * Output must be empty. Failure leaves output unchanged.
 * Destination masks come from the caller's recovered graphics format. */
int vertrix_image_sprite_processed(VertrixVf *archive, const char *name, uint32_t frame,
                                   const uint32_t masks[3], VertrixSpriteFrame *output);

#endif
