#ifndef VERTRIX_TIMING_H
#define VERTRIX_TIMING_H

#include <stdint.h>

#include "random.h"

typedef struct
{
    uint16_t minimum;
    uint16_t width;
} VertrixDelay;

typedef struct
{
    uint32_t period;
    uint32_t counter;
    uint16_t step;
    uint32_t state;
} VertrixMotion;

/* Original active-piece update, difficulty 0..2 and level 0..9.
 * Nonzero original piece state (+0x168) suppresses parameter changes. */
void vertrix_motion_level(VertrixMotion *motion, int difficulty, int level);
void vertrix_motion_fast(VertrixMotion *motion, int difficulty);

/* Valid original inputs: character 0..18, difficulty 0..2, internal level 0..9.
 * Parameter 0 corresponds to player +0x458; parameters 1 and 2 correspond
 * to +0x45c and +0x460. Their game-loop scheduling is not yet recovered. */
VertrixDelay vertrix_delay(int character, int difficulty, uint32_t level, int parameter);
int vertrix_character_power(int character, int slot);
/* Original 0x4b7cd0: sample the millisecond clock (originally WinMM
 * timeGetTime) into both *first and *second (original globals 0x5bd838 and
 * 0x5bd844). Returns the sample. */
uint32_t vertrix_time_sample(VertrixClock clock, void *context, uint32_t *first, uint32_t *second);

/* Original 0x4b7d10: sample the millisecond clock into *now, take the
 * unsigned difference against *previous (original globals 0x5bd838 and
 * 0x5bd844) when ahead (a still or backwards clock yields zero), store it
 * back into *previous and the value capped at 0xffff into *capped (original
 * global 0x5bd834). Returns the capped difference. */
uint32_t vertrix_time_frame_step(VertrixClock clock, void *context, uint32_t *now,
                                 uint32_t *previous, uint32_t *capped);

#endif
