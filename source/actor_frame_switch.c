#include "actor_frame_switch.h"
#include "word_transition.h"

enum
{
    FIELD_CURRENT = 0x48,
    FIELD_TARGET = 0x4a,
    FIELD_STEP = 0x4c,
    FIELD_FRAME = 0xb8,
    DECAY_STEP = 4,
    SWITCH_RESOURCE = 0x544a18
};

int vertrix_actor_frame_decay(VertrixActorRefresh *state, void *actor, size_t size, uint32_t cycles)
{
    uint32_t word;
    int16_t current;
    if (!vertrix_actor_storage_read(actor, size, FIELD_CURRENT, 2, &word))
    {
        return 0;
    }
    if (word == 0)
    {
        return 1;
    }
    if (!vertrix_actor_storage_write(actor, size, FIELD_TARGET, 2, 0) ||
        !vertrix_actor_storage_write(actor, size, FIELD_STEP, 2, DECAY_STEP))
    {
        return 0;
    }
    current = (int16_t)word;
    vertrix_word_transition(&current, 0, DECAY_STEP, cycles);
    return vertrix_actor_storage_write(actor, size, FIELD_CURRENT, 2, (uint16_t)current) &&
           vertrix_actor_refresh_arm(state, actor, size);
}

int vertrix_actor_frame_switch(VertrixActorRefresh *state, void *actor, size_t size,
                               uint32_t handle, uint32_t frame, const VertrixActorFrameOps *ops,
                               void *context)
{
    uint32_t current;
    if (!vertrix_actor_storage_read(actor, size, FIELD_FRAME, 4, &current))
    {
        return 0;
    }
    if (current == frame)
    {
        return 1;
    }
    ops->attach(handle, SWITCH_RESOURCE, context);
    ops->set_frame(handle, frame, context);
    ops->bind(handle, context);
    return vertrix_actor_refresh_arm(state, actor, size);
}

uint32_t vertrix_actor_frame_decay_full(void *actor, size_t size, uint32_t handle, uint32_t cycles,
                                        VertrixMemoryWrite write, void *context)
{
    uint32_t word;
    if (!vertrix_actor_storage_read(actor, size, FIELD_CURRENT, 2, &word))
    {
        return 0;
    }
    if (!word)
    {
        return handle;
    }
    if (!vertrix_actor_storage_write(actor, size, FIELD_TARGET, 2, 0) ||
        !vertrix_actor_storage_write(actor, size, FIELD_STEP, 2, DECAY_STEP))
    {
        return 0;
    }
    int16_t current = (int16_t)(uint16_t)word;
    vertrix_word_transition(&current, 0, DECAY_STEP, cycles);
    vertrix_actor_storage_write(actor, size, FIELD_CURRENT, 2, (uint16_t)current);
    return vertrix_actor_refresh_arm_full(actor, size, handle, write, context);
}

uint32_t vertrix_actor_frame_switch_full(void *actor, size_t size, uint32_t handle, uint32_t frame,
                                         const VertrixCalls *runtime, VertrixMemoryWrite write,
                                         void *context)
{
    uint32_t current;
    if (!vertrix_actor_storage_read(actor, size, FIELD_FRAME, 4, &current))
    {
        return 0;
    }
    if (current == frame)
    {
        return current;
    }
    vertrix_call(runtime, 0x4ac8d0, handle, SWITCH_RESOURCE, frame, handle, 0);
    vertrix_call(runtime, 0x4ac710, handle, frame, frame, handle, 0);
    vertrix_call(runtime, 0x4ac8a0, handle, frame, frame, handle, 0);
    return vertrix_actor_refresh_arm_full(actor, size, handle, write, context);
}
