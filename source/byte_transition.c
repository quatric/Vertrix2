#include "byte_transition.h"
#include <limits.h>
#include <stddef.h>

static int32_t transition_signed(uint32_t bits)
{
    return bits <= INT32_MAX ? (int32_t)bits : -(int32_t)(UINT32_MAX - bits) - 1;
}

int vertrix_byte_transition(uint8_t *current, uint8_t target, int16_t step, uint32_t cycles)
{
    if (!current)
    {
        return -1;
    }
    uint32_t distance = cycles * (uint32_t)(int32_t)step;
    int32_t value = *current;
    if (*current > target)
    {
        value = transition_signed((uint32_t)(int32_t)*current - distance);
        if (value < target)
        {
            value = target;
        }
    }
    else if (*current < target)
    {
        value = transition_signed((uint32_t)(int32_t)*current + distance);
        if (value > target)
        {
            value = target;
        }
    }
    *current = (uint8_t)value;
    return *current != target;
}
