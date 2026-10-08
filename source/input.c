#include "input.h"
#include "actor_storage.h"

#include <stdlib.h>
#include <string.h>

void vertrix_input_repeat_start(VertrixInputRepeat *repeat, const uint32_t payload[3])
{
    repeat->counter = 0;
    repeat->period = repeat->initial_delay;
    repeat->enabled = 1;
    for (unsigned i = 0; i < 3; i++)
    {
        repeat->payload[i] = payload[i];
    }
}

void vertrix_input_repeat_stop(VertrixInputRepeat *repeat)
{
    repeat->enabled = 0;
}

int vertrix_input_repeat_start_full(void *actor, size_t size, uint32_t actor_handle, uint32_t edx,
                                    uint32_t ebx, uint32_t ecx, uint32_t *result)
{
    if (!actor || size < 0x5b || !result)
    {
        return 0;
    }
    uint32_t delay;
    vertrix_actor_storage_write(actor, size, 0x44, 4, 0);
    vertrix_actor_storage_read(actor, size, 0x3c, 4, &delay);
    vertrix_actor_storage_write(actor, size, 0x48, 4, delay);
    vertrix_actor_storage_write(actor, size, 0x5a, 1, 1);
    vertrix_actor_storage_write(actor, size, 0x4c, 4, edx);
    vertrix_actor_storage_write(actor, size, 0x50, 4, ebx);
    vertrix_actor_storage_write(actor, size, 0x54, 4, ecx);
    *result = actor_handle;
    return 1;
}

int vertrix_input_repeat_stop_full(void *actor, size_t size, uint32_t actor_handle,
                                   uint32_t *result)
{
    if (!result || !vertrix_actor_storage_write(actor, size, 0x5a, 1, 0))
    {
        return 0;
    }
    *result = actor_handle;
    return 1;
}

uint32_t vertrix_input_repeat_tick(VertrixInputRepeat *repeat, uint32_t elapsed)
{
    if (repeat->enabled != 1 || repeat->repeat_delay == 0)
    {
        return 0;
    }
    repeat->counter += elapsed;
    if (repeat->counter < repeat->period)
    {
        return 0;
    }
    uint32_t count = repeat->counter / (repeat->period ? repeat->period : 1);
    repeat->counter = 0;
    repeat->period = repeat->repeat_delay;
    return count;
}

int vertrix_input_repeat_tick_full(VertrixInputRepeat *repeat, uint32_t actor_handle,
                                   uint32_t elapsed, const VertrixCalls *calls, uint32_t *result)
{
    if (!repeat || !result)
    {
        return 0;
    }
    if (repeat->enabled != 1 || repeat->repeat_delay == 0)
    {
        *result = actor_handle;
        return 1;
    }
    repeat->counter += elapsed;
    if (repeat->counter < repeat->period)
    {
        *result = 0;
        return 1;
    }
    uint32_t count = repeat->counter / (repeat->period ? repeat->period : 1);
    repeat->counter = 0;
    repeat->period = repeat->repeat_delay;
    uint32_t returned = repeat->repeat_delay;
    for (uint32_t i = 0; i < count; ++i)
    {
        if (!calls || !calls->call)
        {
            return 0;
        }
        returned = vertrix_call(calls, 0x475b20, actor_handle, repeat->payload[0],
                                repeat->payload[1], repeat->payload[2], 0);
    }
    *result = returned;
    return 1;
}

struct VertrixInputNode
{
    VertrixInputEvent event;
    VertrixInputNode *next;
};

void vertrix_input_queue_init(VertrixInputQueue *queue, uint8_t mode)
{
    memset(queue, 0, sizeof(*queue));
    queue->mode = mode;
}

void vertrix_input_queue_acknowledge(VertrixInputQueue *queue)
{
    memset(&queue->current, 0, sizeof(queue->current));
}

int vertrix_input_queue_acknowledge_full(void *actions, size_t size, uint32_t base_handle,
                                         uint32_t index, VertrixMemoryWrite write, void *context,
                                         uint32_t *result)
{
    size_t offset = (size_t)(index & 0xffff) * 0x60;
    if (!actions || !write || !result || offset > size || size - offset < 0x1c)
    {
        return 0;
    }
    uint32_t handle = base_handle + (uint32_t)offset;
    if (!write(0x54d634, 4, handle, context))
    {
        return 0;
    }
    vertrix_actor_storage_write(actions, size, offset + 0x14, 2, 0);
    vertrix_actor_storage_write(actions, size, offset + 0x18, 4, 0);
    vertrix_actor_storage_write(actions, size, offset + 4, 1, 0);
    vertrix_actor_storage_write(actions, size, offset + 8, 4, 0);
    vertrix_actor_storage_write(actions, size, offset + 0xc, 4, 0);
    vertrix_actor_storage_write(actions, size, offset + 0x10, 4, 0);
    *result = handle + 4;
    return 1;
}

int vertrix_input_queue_push(VertrixInputQueue *queue, const VertrixInputEvent *event)
{
    VertrixInputNode *node = malloc(sizeof(*node));
    if (!node)
    {
        return 0;
    }
    node->event = *event;
    node->next = NULL;
    if (queue->tail)
    {
        queue->tail->next = node;
    }
    else
    {
        queue->head = node;
    }
    queue->tail = node;
    queue->count++;
    return 1;
}

void vertrix_input_queue_consume(VertrixInputQueue *queue)
{
    vertrix_input_queue_acknowledge(queue);
    if (!queue->head)
    {
        return;
    }
    VertrixInputNode *node = queue->head;
    queue->current = node->event;
    queue->head = node->next;
    queue->count--;
    if (!queue->head)
    {
        queue->tail = NULL;
    }
    free(node);
}

int vertrix_input_queue_consume_full(uint32_t actor_handle, VertrixMemoryRead read,
                                     VertrixMemoryWrite write, void *memory_context,
                                     const VertrixCalls *calls, uint32_t *result)
{
    if (!read || !write || !result)
    {
        return 0;
    }
    static const unsigned offsets[] = {0x14, 0x18, 4, 8, 0xc, 0x10};
    static const unsigned widths[] = {2, 4, 1, 4, 4, 4};
    for (unsigned i = 0; i < sizeof(offsets) / sizeof(offsets[0]); ++i)
    {
        if (!write(actor_handle + offsets[i], widths[i], 0, memory_context))
        {
            return 0;
        }
    }
    uint32_t count;
    if (!read(actor_handle + 0x2c, 4, &count, memory_context))
    {
        return 0;
    }
    if (!count)
    {
        *result = actor_handle + 0x20;
        return 1;
    }
    if (!calls || !calls->call)
    {
        return 0;
    }
    uint32_t event = vertrix_call(calls, 0x4d8540, actor_handle + 0x20, 0, 0, 0, 0);
    for (unsigned i = 0; i < 4; ++i)
    {
        uint32_t value;
        unsigned width = i ? 4 : 1;
        if (!read(event + i * 4, width, &value, memory_context) ||
            !write(actor_handle + 4 + i * 4, width, value, memory_context))
        {
            return 0;
        }
    }
    uint32_t table, target;
    if (!read(event + 0x18, 4, &table, memory_context) || !read(table, 4, &target, memory_context))
    {
        return 0;
    }
    *result = vertrix_call(calls, target, event, 2, 0, event, 0);
    return 1;
}

void vertrix_input_queue_clear(VertrixInputQueue *queue)
{
    while (queue->head)
    {
        vertrix_input_queue_consume(queue);
    }
    vertrix_input_queue_acknowledge(queue);
}

int vertrix_input_queue_ready(const VertrixInputQueue *queue)
{
    return queue->current.state == 1;
}

int vertrix_input_queue_ready_full(const void *actor, size_t size, uint32_t *result)
{
    uint32_t state;
    if (!result || !vertrix_actor_storage_read(actor, size, 4, 1, &state))
    {
        return 0;
    }
    *result = state == 1;
    return 1;
}

void vertrix_input_queue_update(VertrixInputQueue *queue, VertrixInputUpdate update, int deferred)
{
    if (update == VERTRIX_INPUT_UPDATE_SINGLE && deferred)
    {
        return;
    }
    if (queue->mode == 0)
    {
        if (queue->count)
        {
            vertrix_input_queue_consume(queue);
        }
    }
    else if (queue->mode == 1)
    {
        while (!vertrix_input_queue_ready(queue) && queue->count)
        {
            vertrix_input_queue_consume(queue);
            if (update == VERTRIX_INPUT_UPDATE_SINGLE)
            {
                break;
            }
        }
    }
}

void vertrix_input_action_init(VertrixInputAction *action, uint16_t id, uint8_t mode,
                               uint32_t initial_delay, uint32_t repeat_delay)
{
    memset(action, 0, sizeof(*action));
    vertrix_input_queue_init(&action->queue, mode);
    action->repeat.initial_delay = initial_delay;
    action->repeat.repeat_delay = repeat_delay;
    action->id = id;
}

void vertrix_input_action_clear(VertrixInputAction *action)
{
    vertrix_input_repeat_stop(&action->repeat);
    vertrix_input_queue_clear(&action->queue);
}

static int action_emit(VertrixInputAction *action, uint8_t state, const uint32_t payload[3],
                       int deferred, VertrixInputDeferredSink sink, void *context)
{
    if (deferred)
    {
        return state != 1 || (sink && sink(context, action->id, payload));
    }
    VertrixInputEvent event = {0};
    event.state = state;
    memcpy(event.payload, payload, sizeof(event.payload));
    return vertrix_input_queue_push(&action->queue, &event);
}

int vertrix_input_action_edge(VertrixInputAction *action, const uint32_t payload[3], int pressed,
                              int force, int deferred, VertrixInputDeferredSink sink, void *context)
{
    if (pressed)
    {
        if (!force && !deferred && action->repeat.enabled != 0)
        {
            return 1;
        }
        if (!action_emit(action, 1, payload, deferred, sink, context))
        {
            return 0;
        }
        if (force || !deferred)
        {
            vertrix_input_repeat_start(&action->repeat, payload);
        }
    }
    else
    {
        if (!force && (deferred || action->repeat.enabled == 0))
        {
            return 1;
        }
        if (!action_emit(action, 2, payload, deferred, sink, context))
        {
            return 0;
        }
        vertrix_input_repeat_stop(&action->repeat);
    }
    return 1;
}

int vertrix_input_action_update(VertrixInputAction *action, uint32_t elapsed,
                                VertrixInputUpdate update, int deferred,
                                VertrixInputDeferredSink sink, void *context)
{
    uint32_t count = vertrix_input_repeat_tick(&action->repeat, elapsed);
    for (uint32_t i = 0; i < count; i++)
    {
        if (!action_emit(action, 1, action->repeat.payload, deferred, sink, context))
        {
            return 0;
        }
    }
    vertrix_input_queue_update(&action->queue, update, deferred);
    return 1;
}

int vertrix_input_configure(VertrixInputAction actions[256], const uint16_t controls[9],
                            const uint32_t player_delays[2], uint32_t default_delay)
{
    for (unsigned i = 0; i < 9; i++)
    {
        if (controls[i] >= 256)
        {
            return 0;
        }
    }
    actions[controls[8]].queue.mode = 1;
    for (unsigned i = 0; i < 8; i++)
    {
        uint32_t delay = i % 4 == 3 ? default_delay : player_delays[i / 4];
        actions[controls[i]].repeat.initial_delay = delay;
        actions[controls[i]].repeat.repeat_delay = delay;
    }
    return 1;
}

int vertrix_input_repeat_counter_clear_full(void *actor, size_t size, uint32_t actor_handle,
                                            uint32_t *result)
{
    if (!result || !vertrix_actor_storage_write(actor, size, 0x44, 4, 0))
        return 0;
    *result = actor_handle;
    return 1;
}
int vertrix_input_repeat_counter_advance_full(void *actor, size_t size, uint32_t actor_handle,
                                              uint32_t elapsed, uint32_t *result)
{
    uint32_t counter;
    if (!result || !vertrix_actor_storage_read(actor, size, 0x44, 4, &counter))
        return 0;
    vertrix_actor_storage_write(actor, size, 0x44, 4, counter + elapsed);
    *result = actor_handle;
    return 1;
}
