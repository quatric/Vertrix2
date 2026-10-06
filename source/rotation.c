#include "rotation.h"
#include <stddef.h>

int vertrix_rotation_advance(int16_t *angle, int16_t step, uint32_t cycles,
                             VertrixRotationTrace *trace)
{
    if (!angle || !trace)
    {
        return 0;
    }
    trace->unwrapped = 1;
    if (!step || !cycles)
    {
        return 1;
    }
    trace->iterations = 0;
    for (uint32_t i = 0; i < cycles; ++i)
    {
        uint32_t word = (uint16_t)((uint32_t)(int32_t)*angle + (uint32_t)(int32_t)step);
        int32_t value = word < 32768 ? (int32_t)word : (int32_t)word - 65536;
        if (value >= 360)
        {
            value = (int32_t)(word % 360u);
            trace->unwrapped = 0;
        }
        if (value < 0)
        {
            value = (int32_t)((uint16_t)(value + 360) % 360u);
            trace->unwrapped = 0;
        }
        *angle = (int16_t)value;
        ++trace->iterations;
    }
    return (int)trace->unwrapped;
}
