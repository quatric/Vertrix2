#include "sprite_load_set.h"
#include <stdlib.h>
#include <string.h>

static int direct_bank(VertrixVf *archive, const char *filename, const uint32_t masks[3],
                       VertrixUiSpriteBank *output)
{
    VertrixSpriteFrame first = {0};
    if (!vertrix_image_sprite_processed(archive, filename, 0, masks, &first))
    {
        return 0;
    }
    size_t count = first.frame_count;
    if (!count || count > SIZE_MAX / sizeof(VertrixSpriteFrame))
    {
        vertrix_sprite_free(&first);
        return 0;
    }
    VertrixUiSpriteBank bank = {calloc(count, sizeof(VertrixSpriteFrame)), count};
    if (!bank.frames)
    {
        vertrix_sprite_free(&first);
        return 0;
    }
    bank.frames[0] = first;
    for (size_t i = 1; i < count; ++i)
    {
        if (!vertrix_image_sprite_processed(archive, filename, (uint32_t)i, masks,
                                            &bank.frames[i]) ||
            bank.frames[i].frame_count != count)
        {
            vertrix_ui_sprite_bank_free(&bank);
            return 0;
        }
    }
    *output = bank;
    return 1;
}

void vertrix_sprite_load_set_free(VertrixSpriteLoadSet *set)
{
    if (!set)
    {
        return;
    }
    for (size_t i = 0; i < VERTRIX_SPRITE_LOAD_COUNT; ++i)
    {
        vertrix_ui_sprite_bank_free(&set->banks[i]);
    }
    memset(set, 0, sizeof(*set));
}

int vertrix_sprite_load_set(VertrixVf *archive, const uint8_t settings[19], uint8_t interface_slot,
                            const uint32_t masks[3], size_t first_source,
                            VertrixSpriteLoadSet *output)
{
    if (!output || output->ready || output->map.bindings || output->map.count)
    {
        return 0;
    }
    for (size_t i = 0; i < VERTRIX_SPRITE_LOAD_COUNT; ++i)
    {
        if (output->banks[i].frames || output->banks[i].count)
        {
            return 0;
        }
    }
    VertrixSpriteLoadPlan plan;
    if (!vertrix_sprite_load_plan(archive, settings, interface_slot, &plan))
    {
        return 0;
    }
    VertrixSpriteLoadSet loaded = {0};
    for (size_t i = 0; i < VERTRIX_SPRITE_LOAD_COUNT; ++i)
    {
        int success = plan.entries[i].resource_token == 0x5449fc
                          ? vertrix_ui_sprite_bank_load(archive, plan.entries[i].filename, masks,
                                                        first_source, &loaded.banks[i])
                          : direct_bank(archive, plan.entries[i].filename, masks, &loaded.banks[i]);
        if (!success)
        {
            vertrix_sprite_load_set_free(&loaded);
            return 0;
        }
    }
    *output = loaded;
    for (size_t i = 0; i < VERTRIX_SPRITE_LOAD_COUNT; ++i)
    {
        output->bindings[i].resource_token = plan.entries[i].resource_token;
        output->bindings[i].sprites = &output->banks[i];
    }
    output->map.bindings = output->bindings;
    output->map.count = VERTRIX_SPRITE_LOAD_COUNT;
    output->ready = 1;
    return 1;
}
