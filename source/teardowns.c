#include "teardowns.h"

/* The board's constructor and destructor, the effect slot's constructor and the music load. */

/* Original 0x42ea00: the board eax's destructor with the flags edx: with the flag 4 the array
 * (0x4ccb9f with 0x514a00) is destroyed and freed (0x4ca040); otherwise, under a guard record, the
 * board takes its base methods 0x5149e4, releases its parts (0x42ebc0, 0x42ebe0, 0x42ec00,
 * 0x42ec20, 0x42ec40, 0x42eee0, 0x42eb60, 0x42ec60, 0x430150), deletes its pieces +0xb70 and
 * +0xb78 (method +0 of +0x158 with 2) and its thinker +0xce4 (method +0 of +0x7b4 with 2),
 * destroys its list +0xcec (0x4b5dc0) and its actor base (0x4ac130 with 1), and with the flag 2
 * is freed (0x4ca050). The board. */
uint32_t vertrix_port_board_destroy_42ea00(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x48
    };
    static const uint32_t parts[] = {0x42ebc0, 0x42ebe0, 0x42ec00, 0x42ec20, 0x42ec40,
                                     0x42eee0, 0x42eb60, 0x42ec60, 0x430150};
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t board = entry->eax;
    uint32_t flags = entry->edx;
    uint32_t esi = 0x514964;
    uint32_t edi = 4;
    uint32_t edx = 0x4ec1ec;
    uint32_t object;
    uint32_t eax;
    unsigned index;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    if ((flags & 4) != 0)
    {
        port_set32(&port, ebp, -0x44u, board);
        port_set32(&port, ebp, -0x24u, 1);
        eax = port_call_with(&port, 0x4ccb9f, board, 0x514a00, 1, board, 0, entry->edi, ebp);
        port_set32(&port, ebp, -0x24u, 0);
        port_call_with(&port, 0x4ca040, eax, vertrix_lift_edx, 1, board, 0, entry->edi, ebp);
        return port_return(&port, board, vertrix_lift_edx);
    }
    port_set32(&port, board, 0x158, 0x5149e4);
    port_set32(&port, ebp, -0x1cu, board);
    port_set8(&port, ebp, -0x18u, flags);
    port_set32(&port, ebp, -0x30u, port.env.chain);
    port_set32(&port, ebp, -0x2cu, 0x4ec1ec);
    port_set32(&port, ebp, -0x28u, 0x514964);
    port_set32(&port, ebp, -0x24u, 4);
    for (index = 0; index < sizeof parts / sizeof parts[0]; ++index)
    {
        port_call_with(&port, parts[index], board, edx, flags, board, esi, edi, ebp);
        edx = vertrix_lift_edx;
    }
    object = port_u32(&port, board, 0xb70);
    if (object != 0)
    {
        esi = port_u32(&port, object, 0x158);
        port_call_with(&port, port_u32(&port, esi, 0), object, 2, flags, board, esi, edi, ebp);
    }
    object = port_u32(&port, board, 0xb78);
    if (object != 0)
    {
        esi = port_u32(&port, object, 0x158);
        port_call_with(&port, port_u32(&port, esi, 0), object, 2, flags, board, esi, edi, ebp);
    }
    object = port_u32(&port, board, 0xce4);
    esi = object;
    if (object != 0)
    {
        esi = port_u32(&port, object, 0x7b4);
        port_call_with(&port, port_u32(&port, esi, 0), object, 2, flags, board, esi, edi, ebp);
    }
    edi = 3;
    port_set32(&port, ebp, -0x24u, 3);
    eax = port_call_with(&port, 0x4b5dc0, board + 0xcec, 0, flags, board, esi, edi, ebp);
    port_set32(&port, ebp, -0x24u, 0);
    eax = port_call_with(&port, 0x4ac130, eax - 0xcec, 1, flags, eax - 0xcec, esi, edi, ebp);
    edx = 0;
    port_set32(&port, ebp, -0x24u, 0);
    if ((flags & 2) != 0)
    {
        port_call_with(&port, 0x4ca050, eax, 0, flags, eax, esi, edi, ebp);
        edx = vertrix_lift_edx;
    }
    return port_return(&port, eax, edx);
}

/* Original 0x42e870: the board eax's constructor under a guard record: its actor base (0x4abd70)
 * and list +0xcec (0x4b5db0) are made, it takes the methods 0x5149e4, its tables are made
 * (0x4b2290: +0x220 and +0x87c of 65, +0x988 of 5, +0x9e8 and +0xa2c of 13, +0x324 of 260, +0xbdc
 * of 65), its pieces +0xa60, +0xb70 and +0xb78 cleared, its parts made (0x42f850, 0x42f860,
 * 0x42ef00 to 0x42ef50, 0x42f870, 0x42f880), +0xa68 set to 2, +0xb80 to +0xb8c, +0xbd8 and +0xce0
 * to +0xce8 cleared and +0xb90 set to 1. The board. */
uint32_t vertrix_port_board_construct_42e870(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x38
    };
    static const uint32_t tables[][2] = {{0x220, 0x41}, {0x87c, 0x41},  {0x988, 5},   {0x9e8, 0xd},
                                         {0xa2c, 0xd},  {0x324, 0x104}, {0xbdc, 0x41}};
    static const uint32_t parts[] = {0x42f850, 0x42f860, 0x42ef00, 0x42ef10, 0x42ef20,
                                     0x42ef30, 0x42ef40, 0x42ef50, 0x42f870, 0x42f880};
    static const uint32_t cleared[] = {0xb80, 0xb84, 0xb88, 0xbd8, 0xb8c};
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t board;
    uint32_t eax;
    unsigned index;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x34u, port.env.chain);
    port_set32(&port, ebp, -0x30u, 0x4ec1ec);
    port_set32(&port, ebp, -0x2cu, 0x514950);
    port_set32(&port, ebp, -0x28u, 0);
    port_set8(&port, ebp, -0x1cu, 0);
    port_set32(&port, ebp, -0x20u, entry->eax);
    eax = port_call_with(&port, 0x4abd70, entry->eax, 0x4ec1ec, 0x514950, entry->eax, 0, 1, ebp);
    port_set32(&port, ebp, -0x28u, 1);
    eax = port_call_with(&port, 0x4b5db0, eax + 0xcec, vertrix_lift_edx, 0x514950, entry->eax, 0, 1,
                         ebp);
    board = eax - 0xcec;
    port_set32(&port, ebp, -0x28u, 2);
    port_set32(&port, board, 0x158, 0x5149e4);
    for (index = 0; index < sizeof tables / sizeof tables[0]; ++index)
    {
        port_call_with(&port, 0x4b2290, board + tables[index][0], tables[index][1], 0x514950, board,
                       0, 1, ebp);
    }
    port_set32(&port, board, 0xa60, 0);
    port_set32(&port, board, 0xb70, 0);
    port_set32(&port, board, 0xb78, 0);
    for (index = 0; index < sizeof parts / sizeof parts[0]; ++index)
    {
        port_call_with(&port, parts[index], board, vertrix_lift_edx, 0x514950, board, 0, 1, ebp);
    }
    port_set32(&port, board, 0xa68, 2);
    for (index = 0; index < sizeof cleared / sizeof cleared[0]; ++index)
    {
        port_set32(&port, board, cleared[index], 0);
    }
    port_set32(&port, board, 0xb90, 1);
    port_set32(&port, board, 0xce0, 0);
    port_set32(&port, board, 0xce4, 0);
    port_set32(&port, board, 0xce8, 0);
    return port_return(&port, board, entry->edx);
}

/* Original 0x43d6a0: the effect slot eax's constructor under a guard record: its actor base
 * (0x4abd70) is made, it takes the methods 0x514df4, its tables +0x15c of 500 and +0x92c of 8
 * are made (0x4b2290), +0x94c is cleared and +0x950 set to 1. The slot. */
uint32_t vertrix_port_slot_object_construct_43d6a0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x38
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t slot;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x34u, port.env.chain);
    port_set32(&port, ebp, -0x30u, 0x4ec1ec);
    port_set32(&port, ebp, -0x2cu, 0x514d90);
    port_set32(&port, ebp, -0x28u, 0);
    port_set8(&port, ebp, -0x1cu, 0);
    port_set32(&port, ebp, -0x20u, entry->eax);
    slot = port_call_with(&port, 0x4abd70, entry->eax, 0x4ec1ec, 0x514d90, entry->eax, 0, 1, ebp);
    port_set32(&port, ebp, -0x28u, 1);
    port_set32(&port, slot, 0x158, 0x514df4);
    port_call_with(&port, 0x4b2290, slot + 0x15c, 0x1f4, 0x514d90, slot, 0, 1, ebp);
    port_call_with(&port, 0x4b2290, slot + 0x92c, 8, 0x514d90, slot, 0, 1, ebp);
    port_set32(&port, slot, 0x94c, 0);
    port_set32(&port, slot, 0x950, 1);
    return port_return(&port, slot, entry->edx);
}

/* Original 0x45f3f0: under a guard record, unless the music name 0x4fc080 is 0x50e22f (0x4ccfe0),
 * a name that is found (0x4895e0) is loaded: a player of 0x24 bytes (0x4ca000, 0x487b00) kept at
 * 0x5466c8 opens it (0x487be0), and on failure is deleted (method +4 with 2) and cleared; a name
 * not found becomes 0x50e265. The guard record's chain. */
uint32_t vertrix_port_music_load_45f3f0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x30
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t esi = entry->esi;
    uint32_t player;
    uint32_t methods;
    uint32_t offset;
    uint32_t value;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x2cu, port.env.chain);
    port_set32(&port, ebp, -0x28u, 0x4ec1ec);
    port_set32(&port, ebp, -0x24u, 0x51566c);
    port_set32(&port, ebp, -0x20u, 0);
    if (port_call_with(&port, 0x4ccfe0, 0x4fc080, 0x50e22f, 0, 0x51566c, esi, entry->edi, ebp) == 0)
    {
        return port_return(&port, port_u32(&port, ebp, -0x2cu), entry->edx);
    }
    if (port_call_with(&port, 0x4895e0, 0x4fc080, vertrix_lift_edx, 0, 0x51566c, esi, entry->edi,
                       ebp) != 1)
    {
        for (offset = 0;; ++offset)
        {
            value = port_u8(&port, 0, 0x50e265 + offset);
            port_set8(&port, 0, 0x4fc080 + offset, value);
            if (value == 0)
            {
                break;
            }
        }
        return port_return(&port, port_u32(&port, ebp, -0x2cu), entry->edx);
    }
    player =
        port_call_with(&port, 0x4ca000, 0x24, vertrix_lift_edx, 0, 0x51566c, esi, entry->edi, ebp);
    if (player != 0)
    {
        esi = 1;
        port_set32(&port, ebp, -0x18u, player);
        port_set32(&port, ebp, -0x20u, 1);
        player = port_call_with(&port, 0x487b00, player, vertrix_lift_edx, 0, 0x51566c, esi,
                                entry->edi, ebp);
        port_set32(&port, ebp, -0x20u, 0);
    }
    port_set32(&port, 0, 0x5466c8, player);
    if (port_call_with(&port, 0x487be0, player, 0x4fc080, 0, 0x51566c, esi, entry->edi, ebp) == 0)
    {
        player = port_u32(&port, 0, 0x5466c8);
        if (player != 0)
        {
            methods = port_u32(&port, player, 0);
            port_call_with(&port, port_u32(&port, methods, 4), player, 2, 0, methods, esi,
                           entry->edi, ebp);
        }
        port_set32(&port, 0, 0x5466c8, 0);
    }
    port_set32(&port, ebp, -0x20u, 0);
    return port_return(&port, port_u32(&port, ebp, -0x2cu), entry->edx);
}
