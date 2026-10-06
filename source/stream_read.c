#include "stream_read.h"
#include "actor_storage.h"

enum
{
    STREAM_POSITION = 4,
    STREAM_END = 8
};

typedef struct
{
    uint32_t position;
    uint32_t remaining;
    uint32_t request;
    uint32_t count;
} Plan;

static int plan_read(const void *stream, size_t size, uint32_t item_size, uint32_t count,
                     Plan *plan)
{
    uint32_t end;
    if (!vertrix_actor_storage_read(stream, size, STREAM_POSITION, 4, &plan->position) ||
        !vertrix_actor_storage_read(stream, size, STREAM_END, 4, &end))
    {
        return 0;
    }
    plan->request = item_size * count;
    plan->remaining = end - plan->position;
    plan->count = plan->request;
    if (plan->request > plan->remaining)
    {
        plan->count = plan->remaining;
    }
    return 1;
}

static void consume(void *stream, size_t size, const Plan *plan, uint8_t *destination,
                    VertrixStreamFetch fetch, void *context)
{
    if (plan->count > 0)
    {
        fetch(context, plan->position, destination, plan->count);
        vertrix_actor_storage_write(stream, size, STREAM_POSITION, 4, plan->position + plan->count);
    }
}

int vertrix_stream_read_exact(void *stream, size_t size, uint32_t item_size, uint32_t count,
                              uint8_t *destination, VertrixStreamFetch fetch, void *context,
                              uint32_t *complete)
{
    Plan plan;
    if (!fetch || !complete || !plan_read(stream, size, item_size, count, &plan))
    {
        return 0;
    }
    *complete = plan.request <= plan.remaining;
    consume(stream, size, &plan, destination, fetch, context);
    return 1;
}

int vertrix_stream_read(void *stream, size_t size, uint32_t item_size, uint32_t count,
                        uint8_t *destination, VertrixStreamFetch fetch, void *context,
                        uint32_t *bytes_read)
{
    Plan plan;
    if (!fetch || !bytes_read || !plan_read(stream, size, item_size, count, &plan))
    {
        return 0;
    }
    *bytes_read = plan.count;
    consume(stream, size, &plan, destination, fetch, context);
    return 1;
}

int vertrix_stream_skip(void *stream, size_t size, int32_t delta, uint32_t *applied)
{
    uint32_t position;
    uint32_t end;
    if (!applied || !vertrix_actor_storage_read(stream, size, STREAM_POSITION, 4, &position) ||
        !vertrix_actor_storage_read(stream, size, STREAM_END, 4, &end))
    {
        return 0;
    }
    uint32_t amount;
    if (delta < 0)
    {
        amount = 0u - (uint32_t)delta;
    }
    else
    {
        amount = (uint32_t)delta;
        if (amount >= end - position)
        {
            amount = end - position;
        }
    }
    vertrix_actor_storage_write(stream, size, STREAM_POSITION, 4, position + amount);
    *applied = amount;
    return 1;
}
