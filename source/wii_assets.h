#ifndef VERTRIX_WII_ASSETS_H
#define VERTRIX_WII_ASSETS_H
#include "assets.h"
#include "wii_texture.h"

typedef struct
{
    VertrixWiiTexture frames[7][8];
    VertrixAnimationRange delays[7];
    unsigned ready;
} VertrixWiiBlockSet;

/* Requires initialized GX. Load one original character directly from VF.
 * Output must be zero initialized. Preserved on failure; owns texture memory.
 * Filtering is explicit. Missing original resource rows fail without substitution. */
int vertrix_wii_block_set_load(VertrixVf *archive, uint32_t character, uint8_t filter,
                               VertrixWiiBlockSet *output);
/* Synchronizes GX before releasing textures. Safe on zero initialized storage. */
void vertrix_wii_block_set_free(VertrixWiiBlockSet *set);
typedef struct
{
    VertrixWiiTexture texture;
    uint32_t frame_count;
    uint32_t metadata[10];
} VertrixWiiSpriteFrame;

/* Original processed SPR frame plus all descriptor fields, loaded directly
 * from VF. Requires GX and zero initialized output; preserves it on failure. */
int vertrix_wii_sprite_frame_load(VertrixVf *archive, const char *name, uint32_t frame,
                                  uint8_t filter, VertrixWiiSpriteFrame *output);
void vertrix_wii_sprite_frame_free(VertrixWiiSpriteFrame *frame);
#endif
