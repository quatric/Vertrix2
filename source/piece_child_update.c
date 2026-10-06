#include "piece_child_update.h"
#include "dword_transition.h"
#include "timer.h"
#include <string.h>

int vertrix_piece_child_construct(void *storage, size_t size, uint32_t frame,
                                  const VertrixPieceChildBounds *bounds, int last_child)
{
    if (!storage || size < VERTRIX_ACTOR_BASE_SIZE || !bounds)
    {
        return 0;
    }
    VertrixPieceChildBounds clip = *bounds;
    vertrix_actor_storage_construct(storage, size);
    vertrix_actor_storage_write(storage, size, 0xb0, 4, 0x544bd8);
    vertrix_actor_storage_write(storage, size, 0xb8, 4, frame);
    vertrix_actor_storage_write(storage, size, 0xd0, 4, 12);
    vertrix_actor_storage_write(storage, size, 0xc0, 4, 24);
    vertrix_actor_storage_write(storage, size, 0x8e, 1, 3);
    vertrix_actor_storage_write(storage, size, 0xa8, 2, (uint16_t)clip.x_min);
    vertrix_actor_storage_write(storage, size, 0xaa, 2, (uint16_t)clip.x_max);
    vertrix_actor_storage_write(storage, size, 0xac, 2, (uint16_t)clip.y_min);
    vertrix_actor_storage_write(storage, size, 0xae, 2, (uint16_t)clip.y_max);
    vertrix_actor_storage_write(storage, size, 0x154, 4, last_child ? 0x44c2b0 : 0x44c2a0);
    return 1;
}

int vertrix_piece_child_frame_update(void *storage, size_t size, uint32_t elapsed,
                                     int clear_refresh, uint32_t resource_token,
                                     const VertrixFrameResource *resource, size_t budget)
{
    uint32_t class_token, interaction, child;
    if (!storage || size < VERTRIX_ACTOR_BASE_SIZE)
    {
        return 0;
    }
    vertrix_actor_storage_read(storage, size, 0x158, 4, &class_token);
    vertrix_actor_storage_read(storage, size, 0x104, 4, &interaction);
    vertrix_actor_storage_read(storage, size, 0x108, 4, &child);
    if (class_token != 0x517af4 || interaction || child)
    {
        return 0;
    }
    uint8_t next[VERTRIX_ACTOR_BASE_SIZE];
    memcpy(next, storage, sizeof(next));
    if (clear_refresh)
    {
        vertrix_actor_storage_write(next, sizeof(next), 0x120, 4, 0);
    }
    if (!vertrix_piece_child_update(next, sizeof(next), elapsed, resource_token, resource, budget))
    {
        return 0;
    }
    memcpy(storage, next, sizeof(next));
    return 1;
}

int vertrix_piece_child_update(void *storage, size_t size, uint32_t elapsed,
                               uint32_t resource_token, const VertrixFrameResource *resource,
                               size_t budget)
{
    uint32_t handler, token;
    if (!storage || size < VERTRIX_ACTOR_BASE_SIZE)
    {
        return 0;
    }
    vertrix_actor_storage_read(storage, size, 0x154, 4, &handler);
    vertrix_actor_storage_read(storage, size, 0xb0, 4, &token);
    if ((handler != 0x44c2a0 && handler != 0x44c2b0 && handler != 0x44c310 &&
         handler != 0x44c370) ||
        (token && (token != resource_token || !resource)))
    {
        return 0;
    }
    uint8_t next[VERTRIX_ACTOR_BASE_SIZE];
    memcpy(next, storage, sizeof(next));
    if (handler != 0x44c2a0)
    {
        VertrixTimer timer;
        vertrix_actor_storage_read(next, sizeof(next), 0xbc, 4, &timer.counter);
        vertrix_actor_storage_read(next, sizeof(next), 0xc0, 4, &timer.period);
        vertrix_timer_advance(&timer, elapsed);
        if (vertrix_timer_due(&timer))
        {
            uint32_t cycles = vertrix_timer_cycles(&timer), bits;
            vertrix_timer_consume(&timer);
            int32_t current;
            vertrix_actor_storage_read(next, sizeof(next), 0x58, 4, &bits);
            memcpy(&current, &bits, sizeof(current));
            int32_t target = handler == 0x44c2b0 ? 60 : 0;
            int32_t step = handler == 0x44c370 ? 8 : 4;
            vertrix_actor_storage_write(next, sizeof(next), 0x5c, 4, (uint32_t)target);
            vertrix_actor_storage_write(next, sizeof(next), 0x60, 4, (uint32_t)step);
            int moving = vertrix_dword_transition(&current, target, step, cycles);
            vertrix_actor_storage_write(next, sizeof(next), 0x58, 4, (uint32_t)current);
            if (!moving)
            {
                uint32_t following = handler == 0x44c2b0   ? 0x44c310
                                     : handler == 0x44c310 ? 0x44c2b0
                                                           : 0x44c2a0;
                vertrix_actor_storage_write(next, sizeof(next), 0x154, 4, following);
            }
        }
        vertrix_actor_storage_write(next, sizeof(next), 0xbc, 4, timer.counter);
    }
    if (token)
    {
        uint32_t frame, descriptor;
        vertrix_actor_storage_read(next, sizeof(next), 0xb8, 4, &frame);
        if (!vertrix_frame_resource_get(resource, frame, budget, &descriptor))
        {
            return 0;
        }
        vertrix_actor_storage_write(next, sizeof(next), 0xb4, 4, descriptor);
    }
    memcpy(storage, next, sizeof(next));
    return 1;
}
