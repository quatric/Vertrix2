#include "ui_sprite_bank.h"
#include <stdlib.h>
#include <string.h>

void vertrix_ui_sprite_bank_free(VertrixUiSpriteBank *bank)
{
    if (!bank)
    {
        return;
    }
    for (size_t i = 0; i < bank->count; i++)
    {
        vertrix_sprite_free(&bank->frames[i]);
    }
    free(bank->frames);
    memset(bank, 0, sizeof(*bank));
}

int vertrix_ui_sprite_bank_load(VertrixVf *archive, const char *name, const uint32_t masks[3],
                                size_t first_source, VertrixUiSpriteBank *output)
{
    if (!output || output->frames || output->count)
    {
        return 0;
    }
    VertrixSpriteFrame first = {0};
    if (!vertrix_image_sprite_processed(archive, name, 0, masks, &first))
    {
        return 0;
    }
    size_t count = first.frame_count;
    if (count < 30 || first_source >= count || first_source == 1 ||
        count > SIZE_MAX / sizeof(VertrixSpriteFrame))
    {
        vertrix_sprite_free(&first);
        return 0;
    }
    VertrixUiSpriteBank loaded = {calloc(count, sizeof(VertrixSpriteFrame)), count};
    if (!loaded.frames)
    {
        vertrix_sprite_free(&first);
        return 0;
    }
    loaded.frames[0] = first;
    for (size_t i = 1; i < count; i++)
    {
        if (!vertrix_image_sprite_processed(archive, name, (uint32_t)i, masks, &loaded.frames[i]) ||
            loaded.frames[i].frame_count != count)
        {
            vertrix_ui_sprite_bank_free(&loaded);
            return 0;
        }
    }
    if (!vertrix_sprite_bank_configure_ui(loaded.frames, count, first_source))
    {
        vertrix_ui_sprite_bank_free(&loaded);
        return 0;
    }
    *output = loaded;
    return 1;
}
