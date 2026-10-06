#include "block_chain.h"
#include "block_fade.h"
#include "block_motion.h"

int vertrix_block_chain_update(VertrixAnimation *animation, const uint32_t *frames,
                               size_t frame_storage, uint32_t elapsed, uint32_t *descriptor,
                               VertrixBlockCombined *chain)
{
    if (!chain ||
        (chain->handler != 0x44d1e0 && chain->handler != 0x44d250 && chain->handler != 0x44d2c0 &&
         chain->handler != 0x44d480 && chain->handler != 0x44d4f0 && chain->handler != 0x44d7d0 &&
         chain->handler != 0x44d840 && chain->handler != 0x44dc80))
    {
        return 0;
    }
    VertrixBlockCombined next = *chain;
    if (next.handler == 0x44d2c0)
    {
        VertrixBlockFade fade = {next.timer,       next.amount,   next.amount_target,
                                 next.amount_step, next.field_93, next.handler};
        if (!vertrix_block_fade_update(animation, frames, frame_storage, elapsed, descriptor,
                                       &fade))
        {
            return 0;
        }
        next.timer = fade.timer;
        next.amount = fade.current;
        next.amount_target = fade.target;
        next.amount_step = fade.step;
        next.field_93 = fade.field_93;
        next.handler = fade.handler == 0x44c940 ? 0x44c860 : fade.handler;
    }
    else
    {
        VertrixBlockMotion motion = {next.timer, next.effect, next.effect_target, next.effect_step,
                                     next.handler};
        uint32_t advanced = next.timer.counter + elapsed;
        if (advanced >= next.timer.period)
        {
            motion.target = next.handler == 0x44d1e0 ? 100 : (next.handler == 0x44d480 ? -100 : 0);
            motion.step = next.handler == 0x44d1e0 ? 10 : 20;
            if (next.handler == 0x44d7d0)
            {
                motion.target = 50;
                motion.step = 10;
            }
        }
        if (!vertrix_block_motion_update(animation, frames, frame_storage, elapsed, descriptor,
                                         &motion))
        {
            return 0;
        }
        next.timer = motion.timer;
        next.effect = motion.y;
        next.effect_target = motion.target;
        next.effect_step = motion.step;
        if (motion.handler == 0x44c860)
        {
            switch (next.handler)
            {
                case 0x44d1e0:
                    next.handler = 0x44d250;
                    break;
                case 0x44d250:
                    next.handler = 0x44d2c0;
                    break;
                case 0x44d480:
                    next.handler = 0x44d4f0;
                    break;
                case 0x44d7d0:
                    next.handler = 0x44d840;
                    break;
                case 0x44d840:
                case 0x44dc80:
                    next.handler = 0x44c860;
                    break;
                case 0x44d4f0:
                    next.handler = 0x44d560;
                    break;
            }
        }
    }
    *chain = next;
    return 1;
}
