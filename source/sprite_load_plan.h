#ifndef VERTRIX_SPRITE_LOAD_PLAN_H
#define VERTRIX_SPRITE_LOAD_PLAN_H
#include "sprite_files.h"

#define VERTRIX_SPRITE_LOAD_COUNT 20
typedef struct
{
    uint8_t settings[19];
    uint8_t interface_slot;
    uint32_t first_source;
    uint32_t artwork_source;
    uint32_t border_source;
} VertrixSpriteSelection;
/* Loader initial values: initialized513c4d..5f/4fbfac/4fbf74 and zero-filled
 * uninitialized53bd09/5466c4. Later runtime settings changes are separate. */
int vertrix_sprite_selection_init(VertrixSpriteSelection *output);

typedef struct
{
    uint32_t resource_token;
    uint8_t slot;
    char filename[256];
} VertrixSpriteLoadEntry;
typedef struct
{
    VertrixSpriteLoadEntry entries[VERTRIX_SPRITE_LOAD_COUNT];
} VertrixSpriteLoadPlan;

/* Original fragment 0x45dca0 filename selections in execution order. settings contains the
 * 19 bytes at original513c4d..513c5f; interface_slot is original53bd09. All are
 * supplied runtime values. Original resource tokens are identifiers, not Wii
 * pointers. Resolve names from VF; invalid selections preserve output. This
 * plans direct sprite loads only; cloning/derived resources/progress are separate. */
int vertrix_sprite_load_plan(VertrixVf *archive, const uint8_t settings[19], uint8_t interface_slot,
                             VertrixSpriteLoadPlan *output);
#endif
