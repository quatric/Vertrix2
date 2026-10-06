#ifndef VERTRIX_UI_ACTOR_FRAME_H
#define VERTRIX_UI_ACTOR_FRAME_H
#include "random.h"
#include "ui_actor_update.h"
/* Original base-class virtual update4ae150/4ade20 for recovered interface
 * actors without interaction target104 or child chain108. clear_refresh is
 * original5bb710==1. Unsupported class/interaction/chain/handler fails before
 * mutation. This is an actor-frame entry point, not scene-wide scheduling. */
int vertrix_ui_actor_frame_update(void *storage, size_t size, const VertrixObjectList *list,
                                  VertrixActorStorageResolve resolve, void *context,
                                  int clear_refresh, int16_t start_y, uint32_t elapsed,
                                  uint32_t *refresh_words, size_t refresh_count,
                                  const VertrixFrameResource *resource_one,
                                  const VertrixFrameResource *resource_other, size_t budget);
/* Same virtual update with shared original RNG598d30 for border callbacks.
 * The older entry point rejects these callbacks without a random state. */
int vertrix_ui_actor_frame_update_random(void *storage, size_t size, const VertrixObjectList *list,
                                         VertrixActorStorageResolve resolve, void *context,
                                         int clear_refresh, int16_t start_y, uint32_t elapsed,
                                         uint32_t *refresh_words, size_t refresh_count,
                                         const VertrixFrameResource *resource_one,
                                         const VertrixFrameResource *resource_other, size_t budget,
                                         VertrixRandom *random);
/* Explicit original4ae150 base call by a derived class. Does not dispatch the
 * class's virtual update; preserves its class token. Same interaction/child
 * and callback restrictions as the base-class virtual entry point. */
int vertrix_ui_actor_base_frame_update_random(
    void *storage, size_t size, const VertrixObjectList *list, VertrixActorStorageResolve resolve,
    void *context, int clear_refresh, int16_t start_y, uint32_t elapsed, uint32_t *refresh_words,
    size_t refresh_count, const VertrixFrameResource *resource_one,
    const VertrixFrameResource *resource_other, size_t budget, VertrixRandom *random);
#endif
