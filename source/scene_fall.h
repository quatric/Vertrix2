#ifndef VERTRIX_SCENE_FALL_H
#define VERTRIX_SCENE_FALL_H
#include "descent.h"
#include "scene_descent.h"
/* Complete original active-piece slice 0x42fbba..0x42fc56, including paused/
 * frozen branches through 0x42fe9e. Resolve all live children; state and piece
 * coordinates belong to the caller. Publish child effects before object
 * movement/locking. Invalid runtime state may follow partial progress. */
int vertrix_scene_fall_tick(VertrixScene *scene, VertrixScenePiece *piece,
                            VertrixDescentState *state, int16_t origin_x, int16_t origin_y,
                            uint32_t elapsed, int paused, uint32_t frozen, uint32_t blink,
                            VertrixSceneResolve resolve, VertrixObjectVisit visit, void *context,
                            uint32_t *failed);
#endif
