#ifndef VERTRIX_BLOCK_ARTWORK_H
#define VERTRIX_BLOCK_ARTWORK_H
#include "assets.h"
#include "frame_resource.h"

typedef struct
{
    VertrixBlockSet set;
    uint32_t descriptors[7][8];
    VertrixFrameResource resources[7];
    unsigned ready;
} VertrixBlockArtwork;

/* Loads original VF artwork, masks, frame ordering and delay ranges.
 * Output must be zero initialized and stay at its original address until freed:
 * resource nodes borrow the embedded descriptor arrays. Descriptor handles are
 * local to this artwork set, numbered 1..56; zero is invalid. */
int vertrix_block_artwork_load(VertrixVf *archive, uint32_t character, const uint32_t masks[3],
                               VertrixBlockArtwork *output);
const VertrixImage *vertrix_block_artwork_image(const VertrixBlockArtwork *artwork,
                                                uint32_t descriptor);
void vertrix_block_artwork_free(VertrixBlockArtwork *artwork);
#endif
