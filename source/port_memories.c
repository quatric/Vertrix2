#include "port_memories.h"

/* The image decoder's memory manager setup, the C runtime's 96 bit compare, two object
 * setters and the application's player release. */

static uint32_t call_frame(Port *port, uint32_t target, uint32_t eax, uint32_t edx, uint32_t ebx,
                           uint32_t ecx, uint32_t esi, uint32_t edi, uint32_t ebp,
                           const uint32_t *stack, unsigned count)
{
    uint32_t result;
    vertrix_lift_in_esi = esi;
    vertrix_lift_in_edi = edi;
    vertrix_lift_in_ebp = ebp;
    result = lift_call_arguments(&port->env, target, eax, edx, ebx, ecx, stack, count);
    vertrix_lift_in_esi = vertrix_lift_in_edi = vertrix_lift_in_ebp = 0;
    return result;
}

/* Original 0x4c5a40: the decoder eax's memory manager: the memory limit (0x4c5c10 with 0x54) is
 * taken and 0x54 bytes are allocated (0x4c5bb0; on failure the system memory is released
 * (0x4c5c20) and the error 0x36 raised); the manager's eleven methods 0x4c4d20 to 0x4c5a00 are
 * set, the maximum 1000000000 at +0x30 and the limit at +0x2c, the pool lists +0x34 to +0x40 and
 * +0x44, +0x48 cleared and the size 0x54 kept at +0x4c, and it is kept at the decoder's +4. The
 * setting 0x51232f (0x4dac40), read by 0x512337 (0x4dacf8) as a number and a letter, sets the
 * limit to the number times 1000, times 1000 again for 'm' or 'M'. */
uint32_t vertrix_port_memory_manager_make_4c5a40(PORT_SIGNATURE)
{
    static const uint32_t methods[] = {0x4c4d20, 0x4c4ea0, 0x4c4f60, 0x4c5030, 0x4c5120, 0x4c5190,
                                       0x4c5200, 0x4c55a0, 0x4c5740, 0x4c58e0, 0x4c5a00};
    enum
    {
        BELOW = 0x18
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t decoder = entry->eax;
    uint32_t manager;
    uint32_t setting;
    uint32_t eax;
    uint32_t value;
    uint32_t letter;
    uint32_t args[4];
    unsigned index;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, decoder, 4, 0);
    port_set32(&port, ebp, -0x14u,
               port_call_with(&port, 0x4c5c10, decoder, 0x54, decoder, entry->ecx, entry->esi,
                              entry->edi, ebp));
    manager = port_call_with(&port, 0x4c5bb0, decoder, vertrix_lift_edx, decoder, entry->ecx,
                             entry->esi, entry->edi, ebp);
    if (manager == 0)
    {
        port_call_with(&port, 0x4c5c20, decoder, vertrix_lift_edx, decoder, manager, entry->esi,
                       entry->edi, ebp);
        port_set32(&port, port_u32(&port, decoder, 0), 0x14, 0x36);
        port_set32(&port, port_u32(&port, decoder, 0), 0x18, manager);
        port_call_with(&port, port_u32(&port, port_u32(&port, decoder, 0), 0), decoder,
                       port_u32(&port, decoder, 0), decoder, manager, entry->esi, entry->edi, ebp);
    }
    for (index = 0; index < sizeof methods / sizeof methods[0]; ++index)
    {
        port_set32(&port, manager, index * 4, methods[index]);
    }
    port_set32(&port, manager, 0x30, 0x3b9aca00);
    port_set32(&port, manager, 0x2c, port_u32(&port, ebp, -0x14u));
    port_set32(&port, manager, 0x38, 0);
    port_set32(&port, manager, 0x40, 0);
    port_set32(&port, manager, 0x34, 0);
    port_set32(&port, manager, 0x3c, 0);
    port_set32(&port, manager, 0x44, 0);
    port_set32(&port, manager, 0x48, 0);
    port_set32(&port, manager, 0x4c, 0x54);
    port_set32(&port, decoder, 4, manager);
    setting = port_call_with(&port, 0x4dac40, 0x51232f, 0xffffffffu, decoder, manager, entry->esi,
                             entry->edi, ebp);
    if (setting == 0)
    {
        return port_return(&port, setting, entry->edx);
    }
    port_set8(&port, ebp, -0x10u, 0x78);
    args[0] = setting;
    args[1] = 0x512337;
    args[2] = ebp - 0x14;
    args[3] = ebp - 0x10;
    eax = call_frame(&port, 0x4dacf8, setting, ebp - 0x14, decoder, manager, entry->esi, entry->edi,
                     ebp, args, 4);
    if ((int32_t)eax <= 0)
    {
        return port_return(&port, eax, entry->edx);
    }
    letter = port_u8(&port, ebp, -0x10u);
    if (letter == 0x6d || letter == 0x4d)
    {
        port_set32(&port, ebp, -0x14u, port_u32(&port, ebp, -0x14u) * 1000);
    }
    value = port_u32(&port, ebp, -0x14u) * 1000;
    port_set32(&port, manager, 0x2c, value);
    return port_return(&port, value, entry->edx);
}

/* Original 0x4e949c: 1 when the 96 bit value eax (high dword +8, then +4, then +0) is below the
 * value edx, compared signed dword by dword, else 0. */
uint32_t vertrix_port_triple_below_4e949c(PORT_SIGNATURE)
{
    Port port;
    uint32_t left = entry->eax;
    uint32_t right = entry->edx;
    uint32_t result = 0;
    unsigned offset;
    port_open(&port, calls, services, globals, entry);
    for (offset = 8;; offset -= 4)
    {
        int32_t a = (int32_t)port_u32(&port, left, offset);
        int32_t b = (int32_t)port_u32(&port, right, offset);
        if (a < b)
        {
            result = 1;
            break;
        }
        if (a != b || offset == 0)
        {
            break;
        }
    }
    return port_return(&port, result, entry->edx);
}

/* Original 0x4b35b0: the object eax's pair +0x170 and +0x174 set to edx and ebx. */
uint32_t vertrix_port_object_set_pair_4b35b0(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, entry->eax, 0x170, entry->edx);
    port_set32(&port, entry->eax, 0x174, entry->ebx);
    return port_return(&port, entry->eax, entry->edx);
}

/* Original 0x4b3fb0: the object made by 0x4b34d0 takes the methods 0x517e44 with +0x17c, +0x180
 * and +0x184 cleared. */
uint32_t vertrix_port_object_make_4b3fb0(PORT_SIGNATURE)
{
    Port port;
    uint32_t object;
    port_open(&port, calls, services, globals, entry);
    object = port_call_with(&port, 0x4b34d0, entry->eax, entry->edx, entry->ebx, entry->ecx,
                            entry->esi, entry->edi, entry->ebp);
    port_set32(&port, object, 0x158, 0x517e44);
    port_set32(&port, object, 0x17c, 0);
    port_set32(&port, object, 0x180, 0);
    port_set32(&port, object, 0x184, 0);
    return port_return(&port, object, vertrix_lift_edx);
}

/* Original 0x411f50: the application eax stops the player 0x5328b4 (0x418870 with 0, its second
 * value kept at 0x5328b8), deletes it (method +4 with 2) when there is one, clears it and the
 * application's +0x1c, sets its process to the normal priority (slots 0x4f1b94 and 0x4f1cb4 with
 * 0x20) and sets 0x5328b0. */
uint32_t vertrix_port_app_player_release_411f50(PORT_SIGNATURE)
{
    Port port;
    uint32_t app = entry->eax;
    uint32_t player;
    uint32_t ebx = entry->ebx;
    uint32_t eax;
    uint32_t args[2];
    port_open(&port, calls, services, globals, entry);
    eax = port_call_with(&port, 0x418870, port_u32(&port, 0, 0x5328b4), 0, ebx, app, entry->esi,
                         entry->edi, entry->ebp);
    port_set32(&port, 0, 0x5328b8, vertrix_lift_edx);
    player = port_u32(&port, 0, 0x5328b4);
    ebx = player;
    if (player != 0)
    {
        ebx = port_u32(&port, player, 0);
        eax = port_call_with(&port, port_u32(&port, ebx, 4), player, 2, ebx, app, entry->esi,
                             entry->edi, entry->ebp);
    }
    port_set32(&port, 0, 0x5328b4, 0);
    port_set32(&port, app, 0x1c, 0);
    eax = call_frame(&port, 0x4f1b94, eax, vertrix_lift_edx, ebx, app, 0, entry->edi, entry->ebp, 0,
                     0);
    args[0] = eax;
    args[1] = 0x20;
    eax = call_frame(&port, 0x4f1cb4, eax, vertrix_lift_edx, ebx, app, 0, 1, entry->ebp, args, 2);
    port_set32(&port, 0, 0x5328b0, 1);
    return port_return(&port, eax, entry->edx);
}
