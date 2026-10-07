#ifndef VERTRIX_UI_SCENE_FRAME_H
#define VERTRIX_UI_SCENE_FRAME_H
#include "ui_actor_frame.h"
typedef int (*VertrixActorStorageMutableResolve)(uint32_t handle, void **storage, size_t *size,
                                                 void *context);
/* Original composition 0x4b6200: snapshot count, read each handle as reached, virtual update.
 * Supports recovered base-class interface actors. Resolver preserves list
 * allocation/count and actor storage lifetime during a frame. On unsupported
 * state/resolution, returns0 after any preceding actors have updated. */
int vertrix_ui_scene_frame_update(const VertrixObjectList *list,
                                  VertrixActorStorageMutableResolve resolve, void *context,
                                  int clear_refresh, int16_t start_y, uint32_t elapsed,
                                  uint32_t *refresh_words, size_t refresh_count,
                                  const VertrixFrameResource *resource_one,
                                  const VertrixFrameResource *resource_other, size_t budget);
/* Preserve shared random consumption in original scene-list order. */
int vertrix_ui_scene_frame_update_random(const VertrixObjectList *list,
                                         VertrixActorStorageMutableResolve resolve, void *context,
                                         int clear_refresh, int16_t start_y, uint32_t elapsed,
                                         uint32_t *refresh_words, size_t refresh_count,
                                         const VertrixFrameResource *resource_one,
                                         const VertrixFrameResource *resource_other, size_t budget,
                                         VertrixRandom *random);
#endif
