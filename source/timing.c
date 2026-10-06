#include "timing.h"

#include "recovered.h"

/* Original 0x00431390: transition only from state zero. */
void vertrix_motion_fast(VertrixMotion *motion, int difficulty)
{
    if (motion->state)
    {
        return;
    }
    motion->state = 1;
    motion->period = piece_fast_period[difficulty];
    motion->step = (uint16_t)piece_fast_step[difficulty];
    motion->counter = 0;
}

/* Original 0x00431400: +0xc0 period, +0xbc counter, +0x1a step.
 * Scheduler units and interpolation remain separate recovery work. */
void vertrix_motion_level(VertrixMotion *motion, int difficulty, int level)
{
    if (motion->state)
    {
        return;
    }
    motion->period = piece_motion_period[difficulty][level];
    motion->step = (uint16_t)piece_motion_step[difficulty][level];
    motion->counter = 0;
}

VertrixDelay vertrix_delay(int character, int difficulty, uint32_t level, int parameter)
{
    uint32_t speed = character_speed[character];
    uint32_t row = (uint32_t)parameter * 2;
    uint32_t minimum = character_delays[difficulty][row][speed];
    uint32_t width = character_delays[difficulty][row + 1][speed];
    if (parameter == 0)
    {
        /* 0x0043b5b0: only this delay gets the internal-level adjustment.
         * Preserve unsigned division and the later 16-bit argument truncation. */
        width >>= 1;
        minimum += width - width * level / 9;
    }
    VertrixDelay result = {(uint16_t)minimum, (uint16_t)width};
    return result;
}

int vertrix_character_power(int character, int slot)
{
    return character_powers[character][slot];
}

uint32_t vertrix_time_sample(VertrixClock clock, void *context, uint32_t *first, uint32_t *second)
{
    uint32_t ticks = clock(context);
    *first = ticks;
    *second = ticks;
    return ticks;
}

uint32_t vertrix_time_frame_step(VertrixClock clock, void *context, uint32_t *now,
                                 uint32_t *previous, uint32_t *capped)
{
    uint32_t ticks = clock(context);
    uint32_t delta = 0;
    *now = ticks;
    if (ticks > *previous)
    {
        delta = ticks - *previous;
        if (delta >= 0xffff)
        {
            delta = 0xffff;
        }
    }
    *previous = ticks;
    *capped = delta;
    return delta;
}
