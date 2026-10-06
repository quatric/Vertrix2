#include "board_effects.h"

static void effect_tick(VertrixBoardEffect *effect, uint32_t parameter, uint32_t elapsed, int first)
{
    effect->parameter = parameter;
    uint32_t enabled = parameter ? 1 : 0;
    if (enabled && !effect->state)
    {
        effect->flash = 1;
        if (first)
        {
            effect->effect = 0;
        }
    }
    else if (!enabled && effect->state == 1)
    {
        effect->flash = 0;
        if (first)
        {
            effect->effect = 0;
        }
    }
    effect->state = enabled;
    if (!enabled)
    {
        effect->blink.counter = 0;
        return;
    }
    vertrix_timer_advance(&effect->blink, elapsed);
    if (vertrix_timer_due(&effect->blink))
    {
        effect->blink.counter = 0;
        if (first)
        {
            effect->effect = effect->flash ? 0 : 0xff38;
        }
        effect->flash = 1u - effect->flash;
    }
    if (first)
    {
        effect->primary_counter = 0;
    }
}

int vertrix_board_effects_tick(VertrixBoardEffects *effects, uint32_t elapsed,
                               VertrixObjectVisit visit, void *context)
{
    if (!effects || !visit || (effects->first && !effects->first_handle) ||
        (effects->second && !effects->second_handle))
    {
        return 0;
    }
    if (effects->first)
    {
        effect_tick(effects->first, effects->first_parameter, elapsed, 1);
        visit(effects->first_handle, 0, context);
    }
    if (effects->second)
    {
        effect_tick(effects->second, effects->second_parameter, elapsed, 0);
        visit(effects->second_handle, 0, context);
    }
    return 1;
}
