#ifndef VERTRIX_RANDOM_H
#define VERTRIX_RANDOM_H

#include <stdint.h>

#define VERTRIX_RANDOM_COUNT 4097

typedef uint32_t (*VertrixClock)(void *context);

/* Original CXRandom samples, with an explicit platform clock dependency. */
typedef struct
{
    uint16_t samples[VERTRIX_RANDOM_COUNT];
    uint16_t position;
    uint32_t seed;
    VertrixClock clock;
    void *clock_context;
} VertrixRandom;

void vertrix_random_seed(VertrixRandom *random, uint32_t seed);
void vertrix_random_clock(VertrixRandom *random, VertrixClock clock, void *context);
uint16_t vertrix_random_modulo(VertrixRandom *random, uint16_t divisor);
uint32_t vertrix_random_range(VertrixRandom *random, uint16_t minimum, uint16_t width);

#endif
