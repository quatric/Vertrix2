#ifndef VERTRIX_TIMING_H
#define VERTRIX_TIMING_H

#include <stdint.h>

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

#endif
