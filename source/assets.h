#ifndef VERTRIX_ASSETS_H
#define VERTRIX_ASSETS_H

#include "image.h"
#include "spawn.h"
#include "vf.h"

/* Original BlocsSpeed.ini has 20 character rows and 14 delay columns.
 * Character indices 0..19; native colors: five normal, stone, bomb.
 * Reads directly from the archive and changes output only on success. */
int vertrix_asset_animation_ranges(VertrixVf *archive, uint32_t character,
                                   VertrixAnimationRange ranges[7]);

typedef struct
{
    char artwork[128];
    char mask[128];
} VertrixBlockFiles;

/* Resolve the character row in original BlocsFileName.ini directly from VF.
 * Includes the image/Blocs/ prefix. Preserves configured missing placeholders;
 * resource existence and fallback decisions are handled separately. */
int vertrix_asset_block_files(VertrixVf *archive, uint32_t character, VertrixBlockFiles *files);

typedef struct
{
    VertrixImage frames[7][8];
    VertrixAnimationRange delays[7];
} VertrixBlockSet;

/* Runtime-owned block resources, using original VF tables and frame ordering.
 * Initialize output to zero. A failure leaves it unchanged and frees partial
 * resources. Destination RGB masks specify the recovered color ordering. */
int vertrix_asset_block_set(VertrixVf *archive, uint32_t character, const uint32_t masks[3],
                            VertrixBlockSet *output);
void vertrix_block_set_free(VertrixBlockSet *set);

#endif
