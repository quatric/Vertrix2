#include "input.h"

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
