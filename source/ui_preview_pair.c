#include "ui_preview_pair.h"
#include "ui_border_actor.h"
#include "ui_companion_actor.h"
#include <string.h>

int vertrix_ui_preview_pair_construct(void *companion, size_t companion_size, void *border,
                                      size_t border_size, size_t index, uint8_t side,
                                      uint32_t linked_identity, uint32_t source,
                                      const VertrixUiSpriteBank *interface_bank,
                                      const VertrixUiSpriteBank *border_bank)
{
    if (!companion || !border || companion_size < VERTRIX_ACTOR_BASE_SIZE ||
        border_size < VERTRIX_ACTOR_BASE_SIZE)
    {
        return 0;
    }
    uintptr_t first = (uintptr_t)companion, second = (uintptr_t)border;
    if ((first <= second && second - first < VERTRIX_ACTOR_BASE_SIZE) ||
        (second < first && first - second < VERTRIX_ACTOR_BASE_SIZE))
    {
        return 0;
    }
    int16_t x, y;
    if (!vertrix_ui_border_actor_position(index, side, &x, &y))
    {
        return 0;
    }
    uint8_t next_companion[VERTRIX_ACTOR_BASE_SIZE], next_border[VERTRIX_ACTOR_BASE_SIZE];
    memcpy(next_companion, companion, sizeof(next_companion));
    memcpy(next_border, border, sizeof(next_border));
    vertrix_ui_companion_actor_construct(next_companion, sizeof(next_companion), x, y,
                                         linked_identity, source, index);
    vertrix_ui_border_actor_construct(next_border, sizeof(next_border), x, y, linked_identity);
    const VertrixImage *image;
    uint32_t origin_x, origin_y;
    if (!vertrix_sprite_actor_image_resource(next_companion, sizeof(next_companion), 0x5449fc,
                                             interface_bank, &image, &origin_x, &origin_y) ||
        !vertrix_sprite_actor_image_resource(next_border, sizeof(next_border), 0x5466a4,
                                             border_bank, &image, &origin_x, &origin_y))
    {
        return 0;
    }
    vertrix_actor_storage_write(next_companion, sizeof(next_companion), 0x154, 4, 0x44ff90);
    vertrix_actor_storage_write(next_border, sizeof(next_border), 0x154, 4, 0x450130);
    memcpy(companion, next_companion, sizeof(next_companion));
    memcpy(border, next_border, sizeof(next_border));
    return 1;
}
