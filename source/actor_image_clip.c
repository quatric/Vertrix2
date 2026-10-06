#include "actor_image_clip.h"

int vertrix_actor_image_clip_offset(const VertrixActorImageBounds *bounds,
                                    const VertrixSpriteClip *clip, uint16_t source_width,
                                    uint8_t scale, uint32_t *output)
{
    if (!bounds || !clip || !output || !source_width || !scale || scale > 16)
    {
        return 0;
    }
    if (scale == 16)
    {
        *output = clip->source_offset;
        return 1;
    }
    uint16_t columns = (uint16_t)((uint32_t)clip->bounds.left - (uint32_t)bounds->x);
    uint16_t rows = (uint16_t)((uint32_t)clip->bounds.top - (uint32_t)bounds->y);
    return vertrix_render_scale_clip_offset(scale, source_width, columns, rows, 0, output);
}

static int16_t clip_word(uint32_t value)
{
    value &= 65535;
    return (int16_t)(value < 32768 ? (int32_t)value : (int32_t)value - 65536);
}

int vertrix_actor_image_clip(const void *storage, size_t size,
                             const VertrixActorImageBounds *bounds, uint16_t target_width,
                             uint16_t target_height, VertrixBoardClip cached_clip,
                             VertrixSpriteClip *output)
{
    if (!storage || size < VERTRIX_ACTOR_BASE_SIZE || !bounds || !output)
    {
        return -1;
    }
    uint32_t mode, left, right, top, bottom;
    vertrix_actor_storage_read(storage, size, 0x8e, 1, &mode);
    vertrix_actor_storage_read(storage, size, 0xa8, 2, &left);
    vertrix_actor_storage_read(storage, size, 0xaa, 2, &right);
    vertrix_actor_storage_read(storage, size, 0xac, 2, &top);
    vertrix_actor_storage_read(storage, size, 0xae, 2, &bottom);
    VertrixBoardClip object_clip = {clip_word(left), clip_word(right), clip_word(top),
                                    clip_word(bottom)};
    return vertrix_sprite_clip_mode(clip_word((uint32_t)bounds->x), clip_word((uint32_t)bounds->y),
                                    (uint16_t)bounds->width, (uint16_t)bounds->height,
                                    (uint8_t)mode, target_width, target_height, object_clip,
                                    cached_clip, output);
}
