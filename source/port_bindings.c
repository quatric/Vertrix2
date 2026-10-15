#include "port_bindings.h"

/* The tables' and buffers' release, the players' key bindings, the events' setup and the image
 * decoder's marker reader. */

static void guard_record(Port *port, uint32_t record, uint32_t guard)
{
    port_set32(port, record, 0, port->env.chain);
    port_set32(port, record, 4, 0x4ec1ec);
    port_set32(port, record, 8, guard);
    port_set32(port, record, 0xc, 0);
}

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

/* Original 0x45e260: the tables are released (0x4874f0 on each in turn, with 0x45e810 and
 * 0x45e820 after the first 24 and 0x45e8f0, 0x45e740 and 0x45e830 at the end). */
uint32_t vertrix_port_table_release_everything_45e260(PORT_SIGNATURE)
{
    static const uint32_t first[] = {0x5466a4, 0x546618, 0x546634, 0x546688, 0x54666c, 0x546650,
                                     0x546538, 0x54651c, 0x546500, 0x5449c4, 0x5449e0, 0x5449fc,
                                     0x544a18, 0x544bf4, 0x544d0c, 0x544c64, 0x544cf0, 0x544cd4,
                                     0x544c9c, 0x544cb8, 0x544c80, 0x544c2c, 0x544c48, 0x544c10};
    static const uint32_t second[] = {0x544a6c, 0x544a88, 0x544aa4, 0x544d28,
                                      0x544b84, 0x544ba0, 0x544bbc, 0x544bd8};
    Port port;
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    unsigned index;
    port_open(&port, calls, services, globals, entry);
    for (index = 0; index < sizeof first / sizeof first[0]; ++index)
    {
        eax = port_call_with(&port, 0x4874f0, first[index], edx, entry->ebx, entry->ecx, entry->esi,
                             entry->edi, entry->ebp);
        edx = vertrix_lift_edx;
    }
    eax = port_call_with(&port, 0x45e810, eax, edx, entry->ebx, entry->ecx, entry->esi, entry->edi,
                         entry->ebp);
    edx = vertrix_lift_edx;
    eax = port_call_with(&port, 0x45e820, eax, edx, entry->ebx, entry->ecx, entry->esi, entry->edi,
                         entry->ebp);
    edx = vertrix_lift_edx;
    for (index = 0; index < sizeof second / sizeof second[0]; ++index)
    {
        eax = port_call_with(&port, 0x4874f0, second[index], edx, entry->ebx, entry->ecx,
                             entry->esi, entry->edi, entry->ebp);
        edx = vertrix_lift_edx;
    }
    eax = port_call_with(&port, 0x45e8f0, eax, edx, entry->ebx, entry->ecx, entry->esi, entry->edi,
                         entry->ebp);
    edx = vertrix_lift_edx;
    eax = port_call_with(&port, 0x45e740, eax, edx, entry->ebx, entry->ecx, entry->esi, entry->edi,
                         entry->ebp);
    edx = vertrix_lift_edx;
    eax = port_call_with(&port, 0x45e830, eax, edx, entry->ebx, entry->ecx, entry->esi, entry->edi,
                         entry->ebp);
    edx = vertrix_lift_edx;
    return port_return(&port, eax, edx);
}

/* Original 0x473490: the keys +0x160, +0x162, +0x164 and +0x166 and then +0x168 to +0x16e of the
 * players 0x540f8c and 0x540f90 are released (0x476140 on 0x54d640). */
uint32_t vertrix_port_player_keys_release_473490(PORT_SIGNATURE)
{
    static const uint32_t keys[] = {0x160, 0x162, 0x164, 0x166, 0x168, 0x16a, 0x16c, 0x16e};
    Port port;
    uint32_t first;
    uint32_t second;
    uint32_t eax = entry->eax;
    unsigned half;
    unsigned index;
    port_open(&port, calls, services, globals, entry);
    first = port_u32(&port, 0, 0x540f8c);
    second = port_u32(&port, 0, 0x540f90);
    for (half = 0; half < 2; ++half)
    {
        for (index = 0; index < 4; ++index)
        {
            eax = port_call_with(&port, 0x476140, 0x54d640,
                                 port_u16(&port, first, keys[half * 4 + index]), second, first,
                                 entry->esi, entry->edi, entry->ebp);
        }
        for (index = 0; index < 4; ++index)
        {
            eax = port_call_with(&port, 0x476140, 0x54d640,
                                 port_u16(&port, second, keys[half * 4 + index]), second, first,
                                 entry->esi, entry->edi, entry->ebp);
        }
    }
    return port_return(&port, eax, entry->edx);
}

/* The key binding shared by 0x4737d0 and 0x473960: the keys are reset (0x476010 on 0x54d640) and
 * the players' keys +0x16c, +0x16e, +0x168 and +0x16a are bound (0x473610) to the codes `codes`
 * and `codes` + 8, the first set going to the player 0x540f90 when 0x532a7c is 1 and to 0x540f8c
 * otherwise. */
static uint32_t key_bind(PORT_SIGNATURE, uint32_t codes)
{
    static const uint32_t keys[] = {0x16c, 0x16e, 0x168, 0x16a};
    Port port;
    uint32_t one;
    uint32_t two;
    uint32_t first;
    uint32_t second;
    uint32_t eax;
    unsigned index;
    port_open(&port, calls, services, globals, entry);
    one = port_u32(&port, 0, 0x540f8c);
    two = port_u32(&port, 0, 0x540f90);
    eax =
        port_call_with(&port, 0x476010, 0x54d640, 0, two, one, entry->esi, entry->edi, entry->ebp);
    if (port_u32(&port, 0, 0x532a7c) == 1)
    {
        first = two;
        second = one;
    }
    else
    {
        first = one;
        second = two;
    }
    for (index = 0; index < 4; ++index)
    {
        eax = port_call_with(&port, 0x473610, port_u16(&port, first, keys[index]),
                             port_u8(&port, 0, codes + index), two, one, entry->esi, entry->edi,
                             entry->ebp);
    }
    for (index = 0; index < 4; ++index)
    {
        eax = port_call_with(&port, 0x473610, port_u16(&port, second, keys[index]),
                             port_u8(&port, 0, codes + 8 + index), two, one, entry->esi, entry->edi,
                             entry->ebp);
    }
    return port_return(&port, eax, entry->edx);
}

/* Original 0x4737d0: the key binding of the codes 0x5bb4ec. */
uint32_t vertrix_port_key_bind_4737d0(PORT_SIGNATURE)
{
    return key_bind(calls, services, globals, entry, 0x5bb4ec);
}

/* Original 0x473960: the key binding of the codes 0x5bb4f0. */
uint32_t vertrix_port_key_bind_473960(PORT_SIGNATURE)
{
    return key_bind(calls, services, globals, entry, 0x5bb4f0);
}

/* Original 0x48b7e0: eleven manual-reset events (slot 0x4f1b30) are made into 0x5bb47c to
 * 0x5bb4a4 and their wait lists 0x5bb4a8 to 0x5bb4e8 filled; 1. */
uint32_t vertrix_port_events_setup_48b7e0(PORT_SIGNATURE)
{
    static const uint32_t lists[][2] = {
        {0x5bb4a8, 0x5bb47c}, {0x5bb4ac, 0x5bb488}, {0x5bb4b0, 0x5bb494}, {0x5bb4b4, 0x5bb484},
        {0x5bb4b8, 0x5bb488}, {0x5bb4bc, 0x5bb494}, {0x5bb4c0, 0x5bb48c}, {0x5bb4c4, 0x5bb488},
        {0x5bb4c8, 0x5bb494}, {0x5bb4cc, 0x5bb490}, {0x5bb4d0, 0x5bb488}, {0x5bb4d4, 0x5bb49c},
        {0x5bb4d8, 0x5bb488}, {0x5bb4dc, 0x5bb494}, {0x5bb4e0, 0x5bb4a0}, {0x5bb4e4, 0x5bb488},
        {0x5bb4e8, 0x5bb494}};
    static const uint32_t args[4] = {0, 1, 0, 0};
    Port port;
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    unsigned index;
    port_open(&port, calls, services, globals, entry);
    for (index = 0; index < 11; ++index)
    {
        eax = call_frame(&port, 0x4f1b30, eax, edx, entry->ebx, entry->ecx, entry->esi, entry->edi,
                         entry->ebp, args, 4);
        edx = vertrix_lift_edx;
        port_set32(&port, 0, 0x5bb47c + index * 4, eax);
    }
    for (index = 0; index < sizeof lists / sizeof lists[0]; ++index)
    {
        port_set32(&port, 0, lists[index][0], port_u32(&port, 0, lists[index][1]));
    }
    return port_return(&port, 1, entry->edx);
}

/* Original 0x4c09e0: the decoder eax's marker reader: 0xac bytes from its pool +4 (method +0) are
 * kept at +0x1b8 with the methods 0x4c0990, 0x4bf940 and 0x4c07d0, the 17 marker handlers +0x1c
 * set to 0x4bf6a0 with their lengths +0x60 cleared, the handlers of the markers 1 and 15 set to
 * 0x4bf270; then the reader is reset (0x4c0990). */
uint32_t vertrix_port_marker_reader_make_4c09e0(PORT_SIGNATURE)
{
    Port port;
    uint32_t decoder = entry->eax;
    uint32_t pool;
    uint32_t reader;
    uint32_t eax;
    unsigned index;
    port_open(&port, calls, services, globals, entry);
    pool = port_u32(&port, decoder, 4);
    reader = port_call_with(&port, port_u32(&port, pool, 0), decoder, 0, 0xac, decoder, pool,
                            entry->edi, entry->ebp);
    port_set32(&port, decoder, 0x1b8, reader);
    port_set32(&port, reader, 0, 0x4c0990);
    port_set32(&port, reader, 4, 0x4bf940);
    port_set32(&port, reader, 8, 0x4c07d0);
    for (index = 0; index < 17; ++index)
    {
        port_set32(&port, reader, 0x1c + index * 4, 0x4bf6a0);
        port_set32(&port, reader, 0x60 + index * 4, 0);
    }
    port_set32(&port, reader, 0x20, 0x4bf270);
    port_set32(&port, reader, 0x58, 0x4bf270);
    eax = port_call_with(&port, 0x4c0990, decoder, reader + 0x40, reader, decoder, pool, entry->edi,
                         entry->ebp);
    return port_return(&port, eax, entry->edx);
}

/* Original 0x475510: under a guard record the buffers 0x54b804 and 0x54b800 are freed (0x4ea190);
 * the guard record's chain. */
uint32_t vertrix_port_release_pair_475510(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x24
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    guard_record(&port, ebp - 0x20, 0x51646c);
    port_call_with(&port, 0x4ea190, port_u32(&port, 0, 0x54b804), 0x4ec1ec, 0, 0x51646c, entry->esi,
                   entry->edi, ebp);
    port_call_with(&port, 0x4ea190, port_u32(&port, 0, 0x54b800), vertrix_lift_edx, 0, 0x51646c,
                   entry->esi, entry->edi, ebp);
    return port_return(&port, port_u32(&port, ebp, -0x20u), entry->edx);
}

/* Original 0x425ae0: the keys 0x54d640 are reset (0x4760c0, 0x476590, 0x4765b0 of 1) and
 * released (0x476140 of the edx left and of 0x3b to 0x42), the players' keys released
 * (0x473490), the pause key 0x532b7c released, and each move key bound up and down (0x476500,
 * 0x4764d0) to its player: 0x532b6c, 0x532b6e and 0x532b70 to 0x532b80, 0x532b72 and 0x532b7a
 * to 0x553644, and 0x532b74, 0x532b76 and 0x532b78 to 0x532b84. */
uint32_t vertrix_port_game_keys_setup_425ae0(PORT_SIGNATURE)
{
    static const uint32_t codes[] = {0x532b6c, 0x532b6e, 0x532b70, 0x532b72,
                                     0x532b74, 0x532b76, 0x532b78, 0x532b7a};
    static const uint32_t owners[] = {0x532b80, 0x532b80, 0x532b80, 0,
                                      0x532b84, 0x532b84, 0x532b84, 0};
    Port port;
    uint32_t eax;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t code;
    unsigned index;
    port_open(&port, calls, services, globals, entry);
    port_call_with(&port, 0x4760c0, 0x54d640, entry->edx, ebx, ecx, esi, edi, ebp);
    port_call_with(&port, 0x476590, 0x54d640, vertrix_lift_edx, ebx, ecx, esi, edi, ebp);
    port_call_with(&port, 0x4765b0, 0x54d640, 1, ebx, ecx, esi, edi, ebp);
    port_call_with(&port, 0x476140, 0x54d640, vertrix_lift_edx, ebx, ecx, esi, edi, ebp);
    eax = 0;
    for (code = 0x3b; code <= 0x42; ++code)
    {
        eax = port_call_with(&port, 0x476140, 0x54d640, code, ebx, ecx, esi, edi, ebp);
    }
    port_call_with(&port, 0x473490, eax, vertrix_lift_edx, ebx, ecx, esi, edi, ebp);
    port_call_with(&port, 0x476140, 0x54d640, port_u16(&port, 0, 0x532b7c), ebx, ecx, esi, edi,
                   ebp);
    for (index = 0; index < 8; ++index)
    {
        if (index == 2)
        {
            ebx = port_u32(&port, 0, owners[index]);
            port_call_with(&port, 0x476500, 0x54d640, port_u16(&port, 0, codes[index]), ebx, ecx,
                           esi, edi, ebp);
            ebx = port_u32(&port, 0, owners[index]);
            ecx = port_u32(&port, 0, 0x553644);
            eax = port_call_with(&port, 0x4764d0, 0x54d640, port_u16(&port, 0, codes[index]), ebx,
                                 ecx, esi, edi, ebp);
            continue;
        }
        ebx = owners[index] != 0 ? port_u32(&port, 0, owners[index]) : ecx;
        port_call_with(&port, 0x476500, 0x54d640, port_u16(&port, 0, codes[index]), ebx, ecx, esi,
                       edi, ebp);
        ebx = owners[index] != 0 ? port_u32(&port, 0, owners[index]) : ecx;
        eax = port_call_with(&port, 0x4764d0, 0x54d640, port_u16(&port, 0, codes[index]), ebx, ecx,
                             esi, edi, ebp);
    }
    return port_return(&port, eax, entry->edx);
}
