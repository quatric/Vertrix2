#include "rtlactorgridupdates.h"

enum
{
    /* The owner's grid of actors: seven rows of four slots, 0x10 bytes a row, from +0x15c. */
    GRID = 0x15c,
    ROW_SIZE = 0x10,
    GRID_SIZE = 0x70,
    ACTOR_METHODS = 0x158,
    METHOD_UPDATE = 4,

    CHAIN_UPDATE = 0x4ae150
};

/* Original 0x429ba0 (eax = the owner): updates the owner's actor chain (0x4ae150), then calls the
 * update method (+4) of every actor in the grid at +0x15c, with the actor in eax, its method table
 * in ecx, the row's address in ebx, the slot's offset in edx and the row's offset in esi, as the
 * original leaves them; the loop goes on from the edx the method hands back. Keeps edx; eax is the
 * last slot's address or what its actor's method returns. */
uint32_t vertrix_port_actor_grid_update_429ba0(PORT_SIGNATURE)
{
    Port port;
    port_open_frame(&port, calls, services, globals, entry, 0);
    const uint32_t owner = entry->eax;
    uint32_t result = port_call_with(&port, CHAIN_UPDATE, owner, entry->edx, entry->ebx, entry->ecx,
                                     entry->esi, owner, entry->ebp);
    for (uint32_t row = 0; row != GRID_SIZE && !port.env.failed;)
    {
        uint32_t slot = 0;
        while (slot != ROW_SIZE && !port.env.failed)
        {
            const uint32_t actor = port_u32(&port, owner + row + slot, GRID);
            result = owner + row + slot;
            if (actor != 0)
            {
                const uint32_t methods = port_u32(&port, actor, ACTOR_METHODS);
                result = port_call_with(&port, port_u32(&port, methods, METHOD_UPDATE), actor, slot,
                                        owner + row, methods, row, owner, entry->ebp);
                slot = vertrix_lift_edx;
            }
            slot += 4;
        }
        row += slot;
    }
    return port_return(&port, result, entry->edx);
}
