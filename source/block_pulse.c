#include "block_pulse.h"

int vertrix_block_pulse_update(VertrixAnimation *animation, const uint32_t *frames,
                               size_t frame_storage, uint32_t elapsed, uint32_t *descriptor,
                               VertrixBlockPulse *pulse)
{
    if (!pulse || (pulse->handler != 0x44c9d0 && pulse->handler != 0x44ca40))
    {
        return 0;
    }
    VertrixBlockMotion next = {pulse->timer, pulse->effect, pulse->target, pulse->step,
                               pulse->handler};
    uint32_t advanced = next.timer.counter + elapsed;
    if (advanced >= next.timer.period)
    {
        next.target = pulse->handler == 0x44c9d0 ? 200 : -200;
        next.step = 4;
    }
    if (!vertrix_block_motion_update(animation, frames, frame_storage, elapsed, descriptor, &next))
    {
        return 0;
    }
    uint32_t handler = next.handler == 0x44c860 ? (pulse->handler == 0x44c9d0 ? 0x44ca40 : 0x44c9d0)
                                                : pulse->handler;
    *pulse = (VertrixBlockPulse){next.timer, next.y, next.target, next.step, handler};
    return 1;
}
