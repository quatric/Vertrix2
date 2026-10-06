#include "actor_value_steps.h"
#include "actor_storage.h"

enum
{
    ACTOR_FRAME_BANK = 0xb0,
    ACTOR_FRAME_INDEX = 0xb8,
    ACTOR_PERIOD = 0xc0,
    ACTOR_PERIOD_BASE = 0xc4,
    ACTOR_PERIOD_SPAN = 0xc8,
    ACTOR_CC = 0xcc,
    ACTOR_D0 = 0xd0,
    ACTOR_D0_BASE = 0xd4,
    ACTOR_D0_SPAN = 0xd8,
    ACTOR_WORD_CURRENT = 0x1e,
    ACTOR_WORD_TARGET = 0x20,
    ACTOR_WORD_STEP = 0x22,
    OBJECT_DWORD_CURRENT = 0x64,
    OBJECT_DWORD_TARGET = 0x68,
    OBJECT_DWORD_STEP = 0x6c
};

int32_t vertrix_step_toward(int32_t current, int32_t target, int32_t step, int32_t count)
{
    uint32_t delta = (uint32_t)step * (uint32_t)count;
    int32_t moved = current;
    if (current > target)
    {
        moved = (int32_t)((uint32_t)current - delta);
        if (moved < target)
        {
            moved = target;
        }
    }
    else if (current < target)
    {
        moved = (int32_t)((uint32_t)current + delta);
        if (moved > target)
        {
            moved = target;
        }
    }
    return moved;
}

int vertrix_actor_progress_quotient(const void *actor, size_t size, uint32_t *quotient)
{
    uint32_t counter;
    uint32_t divisor;
    if (!quotient || !vertrix_actor_storage_read(actor, size, ACTOR_CC, 4, &counter) ||
        !vertrix_actor_storage_read(actor, size, ACTOR_D0, 4, &divisor))
    {
        return 0;
    }
    if (divisor == 0)
    {
        divisor = 1;
    }
    *quotient = counter / divisor;
    return 1;
}

static int randomize(void *actor, size_t size, size_t base_offset, size_t span_offset,
                     size_t target_offset, VertrixActorModulo draw, void *context)
{
    uint32_t span;
    uint32_t base;
    uint32_t previous;
    if (!draw || !vertrix_actor_storage_read(actor, size, span_offset, 2, &span) ||
        !vertrix_actor_storage_read(actor, size, base_offset, 4, &base) ||
        !vertrix_actor_storage_read(actor, size, target_offset, 4, &previous))
    {
        return 0;
    }
    uint16_t sample = draw(context, (uint16_t)span);
    return vertrix_actor_storage_write(actor, size, target_offset, 4, (uint32_t)sample + base);
}

int vertrix_actor_randomize_period(void *actor, size_t size, VertrixActorModulo draw, void *context)
{
    return randomize(actor, size, ACTOR_PERIOD_BASE, ACTOR_PERIOD_SPAN, ACTOR_PERIOD, draw,
                     context);
}

int vertrix_actor_randomize_d0(void *actor, size_t size, VertrixActorModulo draw, void *context)
{
    return randomize(actor, size, ACTOR_D0_BASE, ACTOR_D0_SPAN, ACTOR_D0, draw, context);
}

static int frame_compare(const void *actor, size_t size, uint32_t frame_offset,
                         VertrixActorFrameCount count, void *context, uint32_t *result)
{
    uint32_t handle;
    uint32_t frame;
    if (!count || !result ||
        !vertrix_actor_storage_read(actor, size, ACTOR_FRAME_BANK, 4, &handle) ||
        !vertrix_actor_storage_read(actor, size, ACTOR_FRAME_INDEX, 4, &frame))
    {
        return 0;
    }
    *result = frame + frame_offset == count(context, handle);
    return 1;
}

int vertrix_actor_frame_is_count(const void *actor, size_t size, VertrixActorFrameCount count,
                                 void *context, uint32_t *result)
{
    return frame_compare(actor, size, 0, count, context, result);
}

int vertrix_actor_frame_is_last(const void *actor, size_t size, VertrixActorFrameCount count,
                                void *context, uint32_t *result)
{
    return frame_compare(actor, size, 1, count, context, result);
}

int vertrix_actor_step_word(void *actor, size_t size, int32_t count, uint32_t *unfinished)
{
    uint32_t current;
    uint32_t target;
    uint32_t step;
    if (!unfinished || !vertrix_actor_storage_read(actor, size, ACTOR_WORD_CURRENT, 2, &current) ||
        !vertrix_actor_storage_read(actor, size, ACTOR_WORD_TARGET, 2, &target) ||
        !vertrix_actor_storage_read(actor, size, ACTOR_WORD_STEP, 2, &step))
    {
        return 0;
    }
    int32_t moved = vertrix_step_toward((int16_t)current, (int16_t)target, (int16_t)step, count);
    vertrix_actor_storage_write(actor, size, ACTOR_WORD_CURRENT, 2, (uint32_t)moved & 0xffff);
    *unfinished = ((uint32_t)moved & 0xffff) != target;
    return 1;
}

int vertrix_object_step_dword(void *object, size_t size, int32_t count, uint32_t *unfinished)
{
    uint32_t current;
    uint32_t target;
    uint32_t step;
    if (!unfinished ||
        !vertrix_actor_storage_read(object, size, OBJECT_DWORD_CURRENT, 4, &current) ||
        !vertrix_actor_storage_read(object, size, OBJECT_DWORD_TARGET, 4, &target) ||
        !vertrix_actor_storage_read(object, size, OBJECT_DWORD_STEP, 4, &step))
    {
        return 0;
    }
    int32_t moved = vertrix_step_toward((int32_t)current, (int32_t)target, (int32_t)step, count);
    vertrix_actor_storage_write(object, size, OBJECT_DWORD_CURRENT, 4, (uint32_t)moved);
    *unfinished = (uint32_t)moved != target;
    return 1;
}

int vertrix_actor_consume_progress(void *actor, size_t size)
{
    uint32_t quotient;
    uint32_t counter;
    uint32_t divisor;
    uint32_t product;
    if (!vertrix_actor_progress_quotient(actor, size, &quotient) ||
        !vertrix_actor_storage_read(actor, size, ACTOR_CC, 4, &counter) ||
        !vertrix_actor_storage_read(actor, size, ACTOR_D0, 4, &divisor))
    {
        return 0;
    }
    if (divisor == 0)
    {
        divisor = 1;
    }
    product = quotient * divisor;
    if (product >= counter)
    {
        counter = 0;
    }
    else
    {
        counter -= product;
    }
    return vertrix_actor_storage_write(actor, size, ACTOR_CC, 4, counter);
}
