#include "random.h"

/* Original C runtime rand at 0x004d85fc; unsigned arithmetic preserves the
 * original 32-bit multiply/add overflow on both x86 and PowerPC. */
static uint32_t runtime_random(uint32_t *state)
{
    *state = *state * UINT32_C(0x41c64e6d) + UINT32_C(12345);
    return (*state >> 16) & UINT32_C(0x7fff);
}

/* CXRandom seeded buffer initialization, 0x00482640. Each sample consumes
 * three runtime draws, rather than one draw from a replacement generator. */
void vertrix_random_seed(VertrixRandom *random, uint32_t seed)
{
    uint32_t state = seed;
    random->seed = seed;
    random->position = 0;
    random->clock = 0;
    random->clock_context = 0;
    for (int i = 0; i < VERTRIX_RANDOM_COUNT; i++)
    {
        uint32_t first = runtime_random(&state);
        uint32_t second = runtime_random(&state);
        uint32_t third = runtime_random(&state);
        random->samples[i] = (uint16_t)(first + second + third % 2);
    }
}

/* 0x00482550: reseed initially and after each group of 500 samples.
 * The clock supplies the original time() value in seconds. */
static void refill_clock(VertrixRandom *random)
{
    uint32_t state = random->clock(random->clock_context);
    for (int i = 0; i < VERTRIX_RANDOM_COUNT; i++)
    {
        uint32_t first = runtime_random(&state);
        uint32_t second = runtime_random(&state);
        uint32_t third = runtime_random(&state);
        random->samples[i] = (uint16_t)(first + second + third % 2);
        if ((i + 1) % 500 == 0)
        {
            state = random->clock(random->clock_context);
        }
    }
    random->position = 0;
}

void vertrix_random_clock(VertrixRandom *random, VertrixClock clock, void *context)
{
    random->seed = 0;
    random->clock = clock;
    random->clock_context = context;
    refill_clock(random);
}

/* 0x004826c0, with the mode-dependent refill branch on wrap.
 * Divisor must be nonzero, as in the original valid call contract. */
uint16_t vertrix_random_modulo(VertrixRandom *random, uint16_t divisor)
{
    uint16_t result = random->samples[random->position] % divisor;
    random->position++;
    if (random->position == VERTRIX_RANDOM_COUNT)
    {
        random->position = 0;
        if (random->clock)
        {
            refill_clock(random);
        }
    }
    return result;
}

/* 0x00482770: width zero returns minimum without consuming a sample. */
uint32_t vertrix_random_range(VertrixRandom *random, uint16_t minimum, uint16_t width)
{
    if (width == 0)
    {
        return minimum;
    }
    return (uint32_t)minimum + vertrix_random_modulo(random, width);
}
