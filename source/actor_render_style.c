#include "actor_render_style.h"

int vertrix_actor_render_style(const void *storage, size_t size, VertrixActorRenderStyle *output)
{
    if (!storage || size < VERTRIX_ACTOR_BASE_SIZE || !output)
    {
        return 0;
    }
    const uint8_t *actor = storage;
    uint32_t word;
    vertrix_actor_storage_read(storage, size, 0x48, 2, &word);
    VertrixActorRenderStyle style = {0};
    style.flags.flag_73a = actor[0x8c];
    style.flags.flag_739 = actor[0x4e] == 100 ? 0 : actor[0x93];
    style.flags.effect_00d = actor[0x95];
    style.flags.amount_00e = actor[0x4e];
    style.flags.format_000 = actor[0x52];
    style.flags.format_730 = 13;
    style.flags.transform_00c = actor[0x94];
    style.flags.word_002 = (uint16_t)word;
    style.clip_mode = actor[0x8e];
    style.clip_flag = actor[0x8f];
    style.cycle = actor[0x80];
    style.scale = actor[0x44];
    *output = style;
    return 1;
}
