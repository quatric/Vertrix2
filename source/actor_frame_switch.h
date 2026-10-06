#ifndef VERTRIX_ACTOR_FRAME_SWITCH_H
#define VERTRIX_ACTOR_FRAME_SWITCH_H
#include "actor_refresh_state.h"
/* Supplied boundaries for the unrecovered base actor calls the frame switch makes. The actor
 * operand is the handle, value the original register argument. */
typedef struct
{
    /* Original0x4ac8d0: attach a resource (value is its original address token). */
    void (*attach)(uint32_t actor, uint32_t resource, void *context);
    /* Original0x4ac710: select a frame index. */
    void (*set_frame)(uint32_t actor, uint32_t frame, void *context);
    /* Original0x4ac8a0: bind the frame descriptor. */
    void (*bind)(uint32_t actor, void *context);
} VertrixActorFrameOps;

/* Original0x449360: when word +0x48 is nonzero, set words +0x4a = 0 and +0x4c = 4, move the word
 * +0x48 toward zero by cycles * 4 (the recovered 0x4ad530 arithmetic) and arm the refresh
 * (0x4adfe0). Returns zero for short storage or an invalid refresh index. */
int vertrix_actor_frame_decay(VertrixActorRefresh *state, void *actor, size_t size,
                              uint32_t cycles);

/* Original0x449390: unless the frame index at +0xb8 already equals frame, attach resource
 * 0x544a18, select the frame, bind and arm the refresh. Returns zero for short storage or an
 * invalid refresh index (after the supplied calls were made). */
int vertrix_actor_frame_switch(VertrixActorRefresh *state, void *actor, size_t size,
                               uint32_t handle, uint32_t frame, const VertrixActorFrameOps *ops,
                               void *context);
#endif
