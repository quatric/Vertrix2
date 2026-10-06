#ifndef VERTRIX_ACTOR_RENDER_STYLE_H
#define VERTRIX_ACTOR_RENDER_STYLE_H
#include "actor_storage.h"
#include "render_dispatch.h"
typedef struct
{
    VertrixRenderFlagState flags;
    uint8_t clip_mode, clip_flag, cycle, scale;
} VertrixActorRenderStyle;
/* Original direct preparation4ae4e5..4ae571 and4ae69d..4ae6b5.
 * amount100 clears blend flag739 even when actor93 is nonzero. No guessed
 * effect clamps. This prepares state, not pixels; other preparation modes,
 * clipping, effect tables and drawing remain separate. */
int vertrix_actor_render_style(const void *storage, size_t size, VertrixActorRenderStyle *output);
#endif
