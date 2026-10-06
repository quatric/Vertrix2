#ifndef VERTRIX_SCENE_DESCENT_H
#define VERTRIX_SCENE_DESCENT_H
#include "scene_lock.h"
/* Original 0x42fc2d..0x42fc56/0x42fe81 pixel loop with real object transfer.
 * Uses first 65 scene slots as occupancy. A live piece object must resolve;
 * its native coordinates stay synchronized while falling. Failure flag is
 * original board +0xbd8, changed only when the piece locks. Invalid probes or
 * runtime resolution failures return 0 after any earlier progress. */
int vertrix_scene_descent(VertrixScene *scene, VertrixScenePiece *piece, int16_t origin_x,
                          int16_t origin_y, uint32_t pixels, VertrixSceneResolve resolve,
                          VertrixObjectVisit visit, void *context, uint32_t *failed);
#endif
