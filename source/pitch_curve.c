#include "pitch_curve.h"

enum
{
    ROUNDING = 0x400,
    FRACTION_SHIFT = 11,
    RESULT_SHIFT = 4,
    EXPONENT_START = (int32_t)0xfffe8000u,
    EXPONENT_STEP = 0x6000,
    COEFFICIENT_A = 1928, /* 241 * 8 */
    COEFFICIENT_B = 0x3c1f,
    COEFFICIENT_C = 0xc799,
    COEFFICIENT_D = 0x182ed,
    COEFFICIENT_E = 0xefeb
};

static int32_t multiply(int32_t a, int32_t b)
{
    return (int32_t)((uint32_t)a * (uint32_t)b);
}

static int32_t add(int32_t a, int32_t b)
{
    return (int32_t)((uint32_t)a + (uint32_t)b);
}

/* One Horner step: (accumulator * x + 0x400) >> 11. */
static int32_t step(int32_t accumulator, int32_t x)
{
    return add(multiply(accumulator, x), ROUNDING) >> FRACTION_SHIFT;
}

int32_t vertrix_pitch_curve(uint32_t rate)
{
    int32_t scaled = (int32_t)(rate << VERTRIX_PITCH_SHIFT);
    int32_t x = scaled / VERTRIX_PITCH_BASE_RATE;
    int32_t exponent = EXPONENT_START;
    while (x > VERTRIX_PITCH_LIMIT)
    {
        x = add(x, 1) >> 1;
        exponent = add(exponent, EXPONENT_STEP);
    }
    int32_t a = add(multiply(-COEFFICIENT_A, x), ROUNDING) >> FRACTION_SHIFT;
    a = add(a, COEFFICIENT_B);
    a = step(a, x);
    a = add(a, -COEFFICIENT_C);
    a = step(a, x);
    a = add(a, COEFFICIENT_D);
    a = step(a, x);
    a = add(a, -COEFFICIENT_E);
    return add(a, exponent) >> RESULT_SHIFT;
}
