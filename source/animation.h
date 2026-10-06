#ifndef VERTRIX_ANIMATION_H
#define VERTRIX_ANIMATION_H

#include "timer.h"

typedef enum
{
    VERTRIX_ANIMATION_FORWARD_LOOP,
    VERTRIX_ANIMATION_FORWARD_ONCE,
    VERTRIX_ANIMATION_REVERSE_ONCE,
    VERTRIX_ANIMATION_REVERSE_LOOP
} VertrixAnimationMode;

typedef struct
{
    VertrixTimer timer;
    uint32_t frame;
    uint32_t frame_count;
} VertrixAnimation;

/* Original 0x4ac1f0/250/2b0/310. Returns 1 while playing, 0 when a
 * one-shot attempts to step past its endpoint, -1 for invalid state/mode.
 * Resource decoding supplies frame_count; no guessed sprite counts. */
int vertrix_animation_tick(VertrixAnimation *animation, uint32_t elapsed,
                           VertrixAnimationMode mode);

#endif
