#include "actor_draw_slot.h"
#include "actor_storage.h"

/* Zero rejects, one skips, two completed the primary draw. */
static int primary_draw(const VertrixActorRefresh *state, const void *actor, size_t size,
                        uint32_t surface, uint32_t selector, VertrixActorDraw draw, void *context)
{
    uint32_t mode, ready, expected, a, b, x, y;
    if (!state || !draw || !vertrix_actor_storage_read(actor, size, 0x124, 4, &mode))
    {
        return 0;
    }
    if (mode != 1)
    {
        return 1;
    }
    if (!vertrix_actor_refresh_value(state, actor, size, &ready))
    {
        return 0;
    }
    if (ready != 1)
    {
        return 1;
    }
    if (!vertrix_actor_storage_read(actor, size, 0x138, 4, &expected))
    {
        return 0;
    }
    if (ready != expected)
    {
        return 1;
    }
    if (!vertrix_actor_storage_read(actor, size, 0x12c, 4, &a))
    {
        return 0;
    }
    if (!a)
    {
        return 1;
    }
    if (!vertrix_actor_storage_read(actor, size, 0x130, 4, &b))
    {
        return 0;
    }
    if (!b)
    {
        return 1;
    }
    if (!vertrix_actor_storage_read(actor, size, 0x12a, 2, &y) ||
        !vertrix_actor_storage_read(actor, size, 0x128, 2, &x))
    {
        return 0;
    }
    return draw(surface, selector, (int16_t)x, (int16_t)y, a, b, context) ? 2 : 0;
}

static int secondary_fields(const void *actor, size_t size, uint32_t *a, uint32_t *b, uint32_t *x,
                            uint32_t *y)
{
    return vertrix_actor_storage_read(actor, size, 0x130, 4, b) &&
           vertrix_actor_storage_read(actor, size, 0x12c, 4, a) &&
           vertrix_actor_storage_read(actor, size, 0x12a, 2, y) &&
           vertrix_actor_storage_read(actor, size, 0x128, 2, x);
}

static int companion_draw(const void *companion, size_t size, uint32_t a, uint32_t b, uint32_t x,
                          uint32_t y, VertrixActorDraw draw, void *context)
{
    uint32_t handle, selector;
    return vertrix_actor_storage_read(companion, size, 0x274, 4, &handle) &&
           vertrix_actor_storage_read(companion, size, 0x278, 4, &selector) &&
           draw(handle, selector, (int16_t)x, (int16_t)y, a, b, context);
}

int vertrix_actor_draw_slot(const VertrixActorRefresh *state, const void *actor, size_t size,
                            uint32_t surface, uint32_t selector, const void *companion,
                            size_t companion_size, VertrixActorDraw draw, void *context)
{
    int result = primary_draw(state, actor, size, surface, selector, draw, context);
    if (result != 2)
    {
        return result;
    }
    uint32_t flag, a, b, x, y;
    if (!vertrix_actor_storage_read(actor, size, 0x140, 4, &flag))
    {
        return 0;
    }
    if (flag != 1)
    {
        return 1;
    }
    return secondary_fields(actor, size, &a, &b, &x, &y) &&
           companion_draw(companion, companion_size, a, b, x, y, draw, context);
}

int vertrix_actor_draw_slot_full(const VertrixActorRefresh *state, const void *actor, size_t size,
                                 uint32_t surface, uint32_t selector, const VertrixGlobals *globals,
                                 VertrixActorStorageResolve resolve, void *resolve_context,
                                 VertrixActorDraw draw, void *draw_context)
{
    int result = primary_draw(state, actor, size, surface, selector, draw, draw_context);
    if (result != 2)
    {
        return result;
    }
    uint32_t flag, a, b, x, y;
    if (!vertrix_actor_storage_read(actor, size, 0x140, 4, &flag))
    {
        return 0;
    }
    if (flag != 1)
    {
        return 1;
    }
    if (!secondary_fields(actor, size, &a, &b, &x, &y) || !globals || !globals->read || !resolve)
    {
        return 0;
    }
    const void *companion;
    size_t companion_size;
    uint32_t handle = globals->read(0x544070, globals->context);
    return resolve(handle, &companion, &companion_size, resolve_context) &&
           companion_draw(companion, companion_size, a, b, x, y, draw, draw_context);
}

int vertrix_actor_chain_walk(uint32_t first, uint32_t arg, VertrixChainVisit visit_a,
                             VertrixChainVisit visit_b, VertrixChainNext next, void *context)
{
    uint32_t node = first;
    if (!visit_a || !visit_b || !next)
    {
        return 0;
    }
    for (unsigned count = 0; node != 0; ++count)
    {
        if (count >= 4096 || !visit_a(node, 0, context) || !visit_b(node, arg, context) ||
            !next(node, &node, context))
        {
            return 0;
        }
    }
    return 1;
}
