#include "dword_transition.h"
#include "actor_storage.h"
#include <limits.h>
#include <stddef.h>

static int32_t transition_signed(uint32_t bits)
{
    return bits <= INT32_MAX ? (int32_t)bits : -(int32_t)(UINT32_MAX - bits) - 1;
}

int vertrix_dword_transition(int32_t *current, int32_t target, int32_t step, uint32_t cycles)
{
    if (!current)
    {
        return -1;
    }
    uint32_t distance = cycles * (uint32_t)step;
    if (*current > target)
    {
        *current = transition_signed((uint32_t)*current - distance);
        if (*current < target)
        {
            *current = target;
        }
    }
    else if (*current < target)
    {
        *current = transition_signed((uint32_t)*current + distance);
        if (*current > target)
        {
            *current = target;
        }
    }
    return *current != target;
}

enum
{
    TRANSITION_TARGET = 4,
    TRANSITION_STEP = 8
};

int vertrix_actor_dword_transition(void *actor, size_t size, size_t first, uint32_t cycles,
                                   uint32_t *moving)
{
    uint32_t current, target, step;
    int32_t value;
    if (!vertrix_actor_storage_read(actor, size, first, 4, &current) ||
        !vertrix_actor_storage_read(actor, size, first + TRANSITION_TARGET, 4, &target) ||
        !vertrix_actor_storage_read(actor, size, first + TRANSITION_STEP, 4, &step))
    {
        return 0;
    }
    value = (int32_t)current;
    *moving = (uint32_t)vertrix_dword_transition(&value, (int32_t)target, (int32_t)step, cycles);
    return vertrix_actor_storage_write(actor, size, first, 4, (uint32_t)value);
}
