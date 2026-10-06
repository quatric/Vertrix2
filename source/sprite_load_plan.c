#include "sprite_load_plan.h"

int vertrix_sprite_selection_init(VertrixSpriteSelection *output)
{
    if (!output)
    {
        return 0;
    }
    VertrixSpriteSelection selection = {
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19}, 0, 0, 34, 20};
    *output = selection;
    return 1;
}

int vertrix_sprite_load_plan(VertrixVf *archive, const uint8_t settings[19], uint8_t interface_slot,
                             VertrixSpriteLoadPlan *output)
{
    static const uint32_t resources[VERTRIX_SPRITE_LOAD_COUNT] = {
        0x5449c4, 0x5449e0, 0x5449fc, 0x544a18, 0x544c10, 0x544c48, 0x544c2c,
        0x544c64, 0x544d0c, 0x544c80, 0x544c9c, 0x544cb8, 0x544cd4, 0x544cf0,
        0x546500, 0x54651c, 0x546538, 0x546650, 0x54666c, 0x546688};
    static const uint8_t selectors[VERTRIX_SPRITE_LOAD_COUNT] = {
        1, 2, 255, 0, 4, 6, 5, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 3, 17, 18};
    if (!settings || !output)
    {
        return 0;
    }
    VertrixSpriteLoadPlan plan = {0};
    for (size_t i = 0; i < VERTRIX_SPRITE_LOAD_COUNT; ++i)
    {
        plan.entries[i].resource_token = resources[i];
        plan.entries[i].slot = selectors[i] == 255 ? interface_slot : settings[selectors[i]];
        if (!vertrix_sprite_file(archive, plan.entries[i].slot, plan.entries[i].filename,
                                 sizeof(plan.entries[i].filename)))
        {
            return 0;
        }
    }
    *output = plan;
    return 1;
}
