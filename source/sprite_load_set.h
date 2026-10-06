#ifndef VERTRIX_SPRITE_LOAD_SET_H
#define VERTRIX_SPRITE_LOAD_SET_H
#include "sprite_actor_draw.h"
#include "sprite_load_plan.h"

typedef struct
{
    VertrixUiSpriteBank banks[VERTRIX_SPRITE_LOAD_COUNT];
    VertrixSpriteBankBinding bindings[VERTRIX_SPRITE_LOAD_COUNT];
    VertrixSpriteBankMap map;
    unsigned ready;
} VertrixSpriteLoadSet;

/* Own all20 planned direct banks, with original interface clone/mirror changes
 * on resource5449fc only. Settings/masks/first-source are explicit. Resolve VF
 * names before loading. Zero-init output, keep at a stable address while borrowed
 * by renderers, preserve output on failure. Derived resource builders are separate. */
int vertrix_sprite_load_set(VertrixVf *archive, const uint8_t settings[19], uint8_t interface_slot,
                            const uint32_t masks[3], size_t first_source,
                            VertrixSpriteLoadSet *output);
void vertrix_sprite_load_set_free(VertrixSpriteLoadSet *set);
#endif
