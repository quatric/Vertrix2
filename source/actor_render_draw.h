#ifndef VERTRIX_ACTOR_RENDER_DRAW_H
#define VERTRIX_ACTOR_RENDER_DRAW_H
#include "actor_render_geometry.h"
#include "render_row.h"
/* Direct-coordinate actor sprite drawing with resolved VF frame and format4
 * destination. No borders, callbacks or general transform masks. Returns1
 * dispatched,0 clipped/empty,-1 invalid/unsupported. Failure preserves target
 * and preparation; resolved source pixels are never modified. Inputs and
 * preparation/table backing must remain independent of target pixels. */
int vertrix_actor_render_draw32(const void *storage, size_t size, const VertrixSpriteFrame *frame,
                                VertrixSurface *target, VertrixBoardClip cached_clip,
                                const VertrixRenderWeights *weights,
                                const VertrixRenderColorBank *bank,
                                const VertrixPaletteTables *tables,
                                VertrixRenderPreparation *prepared);
#endif
