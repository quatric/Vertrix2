#include "actor_draw_slot.h"
#include "actor_storage.h"

int vertrix_actor_draw_slot(const VertrixActorRefresh *state, const void *actor, size_t size,
                            uint32_t surface, uint32_t selector, const void *companion,
                            size_t companion_size, VertrixActorDraw draw, void *context)
{
    uint32_t mode, ready, expected, a, b, x, y, flag, comp_handle, comp_selector;
    if (!state || !draw || !vertrix_actor_storage_read(actor, size, 0x124, 4, &mode) ||
        !vertrix_actor_storage_read(actor, size, 0x138, 4, &expected) ||
        !vertrix_actor_storage_read(actor, size, 0x12c, 4, &a) ||
        !vertrix_actor_storage_read(actor, size, 0x130, 4, &b) ||
        !vertrix_actor_storage_read(actor, size, 0x128, 2, &x) ||
        !vertrix_actor_storage_read(actor, size, 0x12a, 2, &y) ||
        !vertrix_actor_storage_read(actor, size, 0x140, 4, &flag))
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
    if (ready != 1 || ready != expected || a == 0 || b == 0)
    {
        return 1;
    }
    int32_t sx = (int16_t)x;
    int32_t sy = (int16_t)y;
    if (flag == 1 &&
        (!vertrix_actor_storage_read(companion, companion_size, 0x274, 4, &comp_handle) ||
         !vertrix_actor_storage_read(companion, companion_size, 0x278, 4, &comp_selector)))
    {
        return 0;
    }
    if (!draw(surface, selector, sx, sy, a, b, context))
    {
        return 0;
    }
    return flag != 1 || draw(comp_handle, comp_selector, sx, sy, a, b, context);
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
