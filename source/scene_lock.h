#ifndef VERTRIX_SCENE_LOCK_H
#define VERTRIX_SCENE_LOCK_H
#include "scene_frame.h"

typedef struct
{
    uint32_t handle;
    uint32_t children[3];
    int16_t x, y;
} VertrixScenePiece;
/* Original 0x431c60: complete object transfer after descent blocks. The active
 * handle must identify this piece. In-board children transfer into cell slots;
 * out-of-board children are destroyed. Child slots clear before destroying the
 * piece. Top <= -3 leaves children for the piece destructor and reports lock=0.
 * Caller owns all objects and supplies actual destructors through visit.
 * Returns API success separately from original lock result. Runtime resolution
 * failure may leave earlier children transferred. No allocation. */
int vertrix_scene_lock(VertrixScene *scene, VertrixScenePiece *piece, int16_t origin_x,
                       int16_t origin_y, VertrixSceneResolve resolve, VertrixObjectVisit visit,
                       void *context, int *locked);
#endif
