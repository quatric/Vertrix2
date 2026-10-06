#ifndef VERTRIX_SCENE_FRAME_H
#define VERTRIX_SCENE_FRAME_H
#include "object_list.h"
#include "scene.h"

/* Resolves every scene/list handle to live object storage. Actual virtual
 * update/destructor handlers remain caller-provided. Module owns no storage. */
typedef struct
{
    VertrixScene *scene;
    VertrixObjectList *list;
    VertrixSceneResolve resolve;
    VertrixObjectVisit visit;
    void *context;
    int16_t origin_x, origin_y;
} VertrixSceneFrame;
/* Compose original board tail with native layout, active parameters, dynamic
 * list update/pruning and flag resets. Returns 0 on invalid/unresolved state.
 * Runtime failure may follow partial progress; valid live handles required.
 * Does not implement preceding board descent/effects or the virtual handlers. */
int vertrix_scene_frame(VertrixSceneFrame *frame);
#endif
