#include "font_stencils.h"
#include "sprite_files.h"
#include <string.h>

void vertrix_font_stencils_free(VertrixFontStencils *stencils)
{
    if (!stencils)
    {
        return;
    }
    vertrix_sprite_free(&stencils->frame6);
    vertrix_sprite_free(&stencils->frame9);
    memset(stencils, 0, sizeof(*stencils));
}

int vertrix_font_stencils_load(VertrixVf *archive, const uint32_t masks[3],
                               VertrixFontStencils *output)
{
    if (!output || !masks || output->frame6.image.rgba || output->frame9.image.rgba ||
        output->frame6.image.width || output->frame6.image.height || output->frame9.image.width ||
        output->frame9.image.height || output->frame6.frame_count || output->frame9.frame_count)
    {
        return 0;
    }
    VertrixFontStencils loaded = {0};
    char name[256];
    if (!vertrix_sprite_file(archive, 17, name, sizeof(name)) ||
        !vertrix_image_sprite_processed(archive, name, 6, masks, &loaded.frame6) ||
        !vertrix_image_sprite_processed(archive, name, 9, masks, &loaded.frame9))
    {
        vertrix_font_stencils_free(&loaded);
        return 0;
    }
    *output = loaded;
    return 1;
}
