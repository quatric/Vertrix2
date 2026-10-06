#include "ui_border_artwork.h"
#include "font_image.h"

int vertrix_ui_border_artwork_build(const VertrixUiSpriteBank *interface,
                                    const VertrixUiSpriteBank *stencils, uint32_t source_index,
                                    uint32_t descriptor_format, VertrixSpriteFrame *output)
{
    if (!interface || !interface->frames || source_index >= interface->count || !stencils ||
        !stencils->frames || stencils->count <= 9 || !output || output->image.rgba ||
        output->image.width || output->image.height || output->frame_count ||
        (descriptor_format >> 24) != 4)
    {
        return 0;
    }
    const VertrixSpriteFrame *source = &interface->frames[source_index];
    const VertrixImage *stencil = &stencils->frames[9].image;
    VertrixSpriteFrame frame = {0};
    if (!vertrix_font_image_stencil(&source->image, stencil, 1, &frame.image))
    {
        return 0;
    }
    frame.frame_count = 1;
    frame.metadata[1] = frame.image.width;
    frame.metadata[2] = frame.image.height;
    frame.metadata[3] = source->metadata[3] + (stencil->width >> 1);
    frame.metadata[4] = source->metadata[4] + (stencil->height >> 1);
    frame.metadata[9] = descriptor_format;
    *output = frame;
    return 1;
}
