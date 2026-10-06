#include "frame_counter.h"

void vertrix_frame_counter_update(VertrixFrameCounter *counter, uint32_t now)
{
    uint32_t elapsed = now - counter->window;
    counter->sample = now;
    if (elapsed < VERTRIX_FRAME_WINDOW)
    {
        return;
    }
    counter->per_second = counter->frames * VERTRIX_FRAME_WINDOW / elapsed;
    counter->frames = 0;
    counter->window = now;
}
