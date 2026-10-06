#include "word_transition.h"
#include <limits.h>
#include <stddef.h>

static int32_t transition_signed(uint32_t bits)
{
    return bits <= INT32_MAX ? (int32_t)bits : -(int32_t)(UINT32_MAX - bits) - 1;
}

int vertrix_word_transition(int16_t *current, int16_t target, int16_t step, uint32_t cycles)
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
    uint32_t word = (uint16_t)value;
    *current = (int16_t)(word < 32768 ? (int32_t)word : (int32_t)word - 65536);
    return *current != target;
}
