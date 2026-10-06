#include "block_artwork.h"
#include <string.h>

int vertrix_block_artwork_load(VertrixVf *archive, uint32_t character, const uint32_t masks[3],
                               VertrixBlockArtwork *output)
{
    if (!output || output->ready)
    {
        return 0;
    }
    if (!vertrix_asset_block_set(archive, character, masks, &output->set))
    {
        return 0;
    }
    for (uint32_t color = 0; color < 7; ++color)
    {
        for (uint32_t frame = 0; frame < 8; ++frame)
        {
            output->descriptors[color][frame] = 1 + color * 8 + frame;
        }
        output->resources[color] =
            (VertrixFrameResource){0, 8, output->descriptors[color], NULL, NULL};
    }
    output->ready = 1;
    return 1;
}

const VertrixImage *vertrix_block_artwork_image(const VertrixBlockArtwork *artwork,
                                                uint32_t descriptor)
{
    if (!artwork || !artwork->ready || descriptor == 0 || descriptor > 56)
    {
        return NULL;
    }
    uint32_t index = descriptor - 1;
    return &artwork->set.frames[index / 8][index % 8];
}

void vertrix_block_artwork_free(VertrixBlockArtwork *artwork)
{
    if (!artwork)
    {
        return;
    }
    vertrix_block_set_free(&artwork->set);
    memset(artwork, 0, sizeof(*artwork));
}
