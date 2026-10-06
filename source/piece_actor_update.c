#include "piece_actor_update.h"
#include "piece_child_update.h"
#include "timer.h"

typedef struct
{
    VertrixActorStorageMutableResolve resolve;
    void *context;
    int clear_refresh;
    uint32_t resource_token;
    const VertrixFrameResource *resource;
    size_t budget;
} PieceUpdateResource;

static int piece_resource_resolve(uint32_t handle, void **storage, size_t *size, void *context)
{
    PieceUpdateResource *piece = context;
    return piece->resolve(handle, storage, size, piece->context);
}

static int piece_resource_update(void *actor, size_t size, uint32_t elapsed, void *context)
{
    PieceUpdateResource *piece = context;
    return vertrix_piece_child_frame_update(actor, size, elapsed, piece->clear_refresh,
                                            piece->resource_token, piece->resource, piece->budget);
}

int vertrix_piece_actor_update_resource(void *parent, size_t parent_size, uint32_t elapsed,
                                        uint16_t row_height,
                                        VertrixActorStorageMutableResolve resolve, void *context,
                                        int clear_refresh, uint32_t resource_token,
                                        const VertrixFrameResource *resource, size_t budget)
{
    if (!resolve)
    {
        return 0;
    }
    PieceUpdateResource piece = {resolve, context, clear_refresh, resource_token, resource, budget};
    return vertrix_piece_actor_update(parent, parent_size, elapsed, row_height,
                                      piece_resource_resolve, piece_resource_update, &piece);
}

int vertrix_piece_actor_update(void *parent, size_t parent_size, uint32_t elapsed,
                               uint16_t row_height, VertrixActorStorageMutableResolve resolve,
                               VertrixPieceActorUpdate update, void *context)
{
    if (!parent || parent_size < 0x188 || !resolve || !update)
    {
        return 0;
    }
    VertrixTimer timer;
    vertrix_actor_storage_read(parent, parent_size, 0xbc, 4, &timer.counter);
    vertrix_actor_storage_read(parent, parent_size, 0xc0, 4, &timer.period);
    vertrix_timer_advance(&timer, elapsed);
    if (vertrix_timer_due(&timer))
    {
        uint32_t cycles = vertrix_timer_cycles(&timer);
        vertrix_timer_consume(&timer);
        vertrix_actor_storage_write(parent, parent_size, 0xbc, 4, timer.counter);
        uint32_t stopped;
        vertrix_actor_storage_read(parent, parent_size, 0x17c, 4, &stopped);
        if (!stopped)
        {
            uint32_t y, step;
            vertrix_actor_storage_read(parent, parent_size, 0x16, 2, &y);
            vertrix_actor_storage_read(parent, parent_size, 0x1a, 2, &step);
            vertrix_actor_storage_write(parent, parent_size, 0x16, 2, y + step * cycles);
        }
    }
    else
    {
        vertrix_actor_storage_write(parent, parent_size, 0xbc, 4, timer.counter);
    }
    for (size_t i = 0; i < 7; ++i)
    {
        uint32_t handle;
        vertrix_actor_storage_read(parent, parent_size, 0x15c + i * 4, 4, &handle);
        if (!handle)
        {
            continue;
        }
        void *actor;
        size_t size;
        if (!resolve(handle, &actor, &size, context) || !update(actor, size, elapsed, context))
        {
            return 0;
        }
    }
    for (size_t i = 0; i < 7; ++i)
    {
        uint32_t handle;
        vertrix_actor_storage_read(parent, parent_size, 0x15c + i * 4, 4, &handle);
        if (!handle)
        {
            continue;
        }
        void *actor;
        size_t size;
        if (!resolve(handle, &actor, &size, context) || !actor || size < 0x5a)
        {
            return 0;
        }
        uint32_t mode, flag, effect;
        vertrix_actor_storage_read(parent, parent_size, 0x180, 4, &mode);
        vertrix_actor_storage_read(parent, parent_size, 0x184, 4, &flag);
        if (mode == 1 && flag == 1)
        {
            effect = UINT32_C(0xff38);
        }
        else
        {
            vertrix_actor_storage_read(actor, size, 0x58, 2, &effect);
        }
        vertrix_actor_storage_write(actor, size, 0x48, 2, effect);
    }
    return vertrix_piece_actor_layout(parent, parent_size, row_height, resolve, context);
}
