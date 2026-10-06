#include "image.h"
#include <stdlib.h>
#include <string.h>

int vertrix_sprite_bank_configure_ui(VertrixSpriteFrame *frames, size_t count, size_t first_source)
{
    if (!frames || count < 30 || first_source >= count || first_source == 1)
    {
        return 0;
    }
    const size_t sources[5] = {first_source, 9, 11, 28, 24};
    const size_t destinations[5] = {1, 10, 12, 29, 25};
    VertrixSpriteFrame replacements[5] = {0};
    for (size_t i = 0; i < 5; i++)
    {
        if (!vertrix_sprite_clone(&frames[sources[i]], &replacements[i]) ||
            !vertrix_image_mirror_horizontal(&replacements[i].image))
        {
            for (size_t j = 0; j < 5; j++)
            {
                vertrix_sprite_free(&replacements[j]);
            }
            return 0;
        }
    }
    for (size_t i = 0; i < 5; i++)
    {
        vertrix_sprite_free(&frames[destinations[i]]);
        frames[destinations[i]] = replacements[i];
    }
    return 1;
}

int vertrix_sprite_bank_replace_mirrored(VertrixSpriteFrame *frames, size_t count,
                                         size_t source_index, size_t destination_index)
{
    if (!frames || source_index >= count || destination_index >= count ||
        source_index == destination_index)
    {
        return 0;
    }
    return vertrix_sprite_replace_mirrored(&frames[source_index], &frames[destination_index]);
}

int vertrix_sprite_replace_mirrored(const VertrixSpriteFrame *source,
                                    VertrixSpriteFrame *destination)
{
    if (!source || !destination || source == destination ||
        (source->image.rgba && source->image.rgba == destination->image.rgba))
    {
        return 0;
    }
    VertrixSpriteFrame cloned = {0};
    if (!vertrix_sprite_clone(source, &cloned))
    {
        return 0;
    }
    if (!vertrix_image_mirror_horizontal(&cloned.image))
    {
        vertrix_sprite_free(&cloned);
        return 0;
    }
    vertrix_sprite_free(destination);
    *destination = cloned;
    return 1;
}

int vertrix_sprite_clone(const VertrixSpriteFrame *source, VertrixSpriteFrame *output)
{
    if (!source || !output || source == output || output->image.rgba || output->image.width ||
        output->image.height || output->frame_count || !source->image.rgba ||
        !source->image.width || !source->image.height ||
        (uint64_t)source->image.width * source->image.height > SIZE_MAX / 4)
    {
        return 0;
    }
    size_t bytes = (size_t)source->image.width * source->image.height * 4;
    unsigned char *pixels = malloc(bytes);
    if (!pixels)
    {
        return 0;
    }
    memcpy(pixels, source->image.rgba, bytes);
    VertrixSpriteFrame cloned = *source;
    cloned.image.rgba = pixels;
    *output = cloned;
    return 1;
}
