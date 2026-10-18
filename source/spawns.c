#include "spawns.h"

/* Picture actor states, the resource row builders, companion and picture actor spawns, the key
 * text reader, object centering and display interface release. */

/* A call handing the callee esi, edi and ebp as given and `count` stack dwords. */
static uint32_t call_frame(Port *port, uint32_t target, uint32_t eax, uint32_t edx, uint32_t ebx,
                           uint32_t ecx, uint32_t esi, uint32_t edi, uint32_t ebp,
                           const uint32_t *stack, unsigned count)
{
    return port_call_registers(port, target, eax, edx, ebx, ecx, esi, edi, ebp, stack, count);
}

/* Original 0x45aea0: on each beat of the actor's picture timer (0x4ac370, 0x4ac390) it restarts
 * it (0x4ac3b0, 0x4ac420) and steps the picture (0x4ac740) once a tick until 0x4ac780 says it
 * ended, then 0x4ac4a0; once it ended the actor shows 0x544a34 at the choice 0x532a68
 * (0x4ac8d0, 0x4ac710), 0x4ac8a0 with 0x45ad20 and 0x4ac8f0. */
uint32_t vertrix_port_picture_play_update_45aea0(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t running = 1;
    uint32_t time;
    uint32_t edx;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_forward(&port, entry, 0x4ac370, actor, entry->edx, entry->ebx, actor);
    result = port_forward_esi(&port, entry, 0x4ac390, actor, vertrix_lift_edx, entry->ebx, actor,
                              running);
    if (result != 1)
    {
        return port_return(&port, result, entry->edx);
    }
    time = port_forward_esi(&port, entry, 0x4ac3b0, actor, vertrix_lift_edx, entry->ebx, actor,
                            running);
    port_forward_esi(&port, entry, 0x4ac420, actor, time, time, actor, running);
    edx = vertrix_lift_edx;
    if (time != 0)
    {
        do
        {
            if (port_forward_esi(&port, entry, 0x4ac780, actor, edx, time, actor, running) != 0)
            {
                running = 0;
                edx = vertrix_lift_edx;
                break;
            }
            port_forward_esi(&port, entry, 0x4ac740, actor, vertrix_lift_edx - 1, time, actor,
                             running);
            edx = vertrix_lift_edx;
        } while (edx != 0);
    }
    result = port_forward_esi(&port, entry, 0x4ac4a0, actor, edx, time, actor, running);
    if (running != 0)
    {
        return port_return(&port, result, entry->edx);
    }
    port_forward_esi(&port, entry, 0x4ac8d0, actor, 0x544a34, time, actor, running);
    port_forward_esi(&port, entry, 0x4ac710, actor, port_u32(&port, 0, 0x532a68), time, actor,
                     running);
    port_forward_esi(&port, entry, 0x4ac8a0, actor, 0x45ad20, time, actor, running);
    result =
        port_forward_esi(&port, entry, 0x4ac8f0, actor, vertrix_lift_edx, time, actor, running);
    return port_return(&port, result, entry->edx);
}

/* Original 0x45af40: on each beat of the actor's second timer (0x4ac600, 0x4ac620) it restarts it
 * (0x4ac640, 0x4ac6b0), moves (0x4aca60, 0x4acab0) and fades (0x4acb00, 0x4adfe0); once all three
 * and the edx 0x4adfe0 leaves give 0 it waits 5 to 9 (0x4826c0 on 0x598d30 with 5, 0x4ac860)
 * and takes the state 0x45b130. */
uint32_t vertrix_port_actor_glide_update_45af40(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t time;
    uint32_t across;
    uint32_t down;
    uint32_t faded;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_forward(&port, entry, 0x4ac600, actor, entry->edx, entry->ebx, actor);
    result = port_forward(&port, entry, 0x4ac620, actor, vertrix_lift_edx, entry->ebx, actor);
    if (result != 1)
    {
        return port_return(&port, result, entry->edx);
    }
    time = port_forward(&port, entry, 0x4ac640, actor, vertrix_lift_edx, entry->ebx, actor);
    port_forward(&port, entry, 0x4ac6b0, actor, vertrix_lift_edx, time, actor);
    across = port_forward(&port, entry, 0x4aca60, actor, time, time, actor);
    down = port_forward_esi(&port, entry, 0x4acab0, actor, time, time, actor, across);
    faded = port_call_with(&port, 0x4acb00, actor, time, time, actor, across, down, entry->ebp);
    result = port_call_with(&port, 0x4adfe0, actor, faded, time, actor, across, down, entry->ebp);
    if (across != 0 || down != 0 || vertrix_lift_edx != 0)
    {
        return port_return(&port, result, entry->edx);
    }
    result = port_call_with(&port, 0x4826c0, 0x598d30, 5, time, actor, across, down, entry->ebp);
    port_call_with(&port, 0x4ac860, actor, (result & 0xffff) + 5, time, actor, across, down,
                   entry->ebp);
    result =
        port_call_with(&port, 0x4ac8f0, actor, 0x45b130, time, actor, across, down, entry->ebp);
    return port_return(&port, result, entry->edx);
}

/* Original 0x45ba30: the board sums the player's marks (0x439260 into +0x404 and +0x41c): any
 * marked, +0x418 0, the state 0x45bad0 and the opponent (+0x3b0) gains (0x43ac00); none, the
 * opponent 0x43acd0. The board draws and, with none marked, the view is set up again
 * (0x43bbf0). */
uint32_t vertrix_port_effect_marks_sum_45ba30(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x20
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t player = entry->eax;
    uint32_t board;
    uint32_t opponent;
    uint32_t edi;
    uint32_t methods;
    uint32_t result;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x1cu, player);
    board = port_u32(&port, player, 0x15c);
    port_set32(&port, ebp, -0x18u, 0);
    opponent = port_u32(&port, player, 0x3b0);
    edi = opponent;
    port_call_with(&port, 0x439260, board, player + 0x404, player + 0x41c, player, board, edi, ebp);
    if (port_u32(&port, player, 0x41c) != 0)
    {
        port_set32(&port, player, 0x418, 0);
        port_call_with(&port, 0x4ac8f0, player, 0x45bad0, player + 0x41c, player, board, edi, ebp);
        port_call_with(&port, 0x43ac00, opponent, vertrix_lift_edx, player + 0x41c, player, board,
                       edi, ebp);
    }
    else
    {
        edi = 1;
        port_call_with(&port, 0x43acd0, opponent, vertrix_lift_edx, player + 0x41c, player, board,
                       edi, ebp);
        port_set32(&port, ebp, -0x18u, edi);
    }
    methods = port_u32(&port, board, 0x158);
    result = port_call_with(&port, port_u32(&port, methods, 4), board, methods, player + 0x41c,
                            player, board, edi, ebp);
    if (port_u32(&port, ebp, -0x18u) == 1)
    {
        result = port_call_with(&port, 0x43bbf0, port_u32(&port, ebp, -0x1cu), vertrix_lift_edx,
                                player + 0x41c, player, board, edi, ebp);
    }
    return port_return(&port, result, entry->edx);
}

/* Original 0x45e590: the seven resource rows (0x546554 on, 0x1c apart; their tables 0x544ac0 on)
 * are set to 8 entries (0x487640) and each entry n is the table's entry n (0x4877f0) made by
 * 0x4831b0 against the base 0x4877f0 gives for 0x546538 with 9 (0x487850). */
uint32_t vertrix_port_resource_rows_build_45e590(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x28
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t base;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = 0x544ac0;
    uint32_t esi;
    uint32_t edi;
    uint32_t result = 0;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    base = port_call_with(&port, 0x4877f0, 0x546538, 9, ebx, ecx, entry->esi, entry->edi, ebp);
    port_set32(&port, ebp, -0x18u, base);
    port_set32(&port, ebp, -0x1cu, ecx);
    port_set32(&port, ebp, -0x20u, 0x546554);
    port_set32(&port, ebp, -0x24u, ecx + 0xc4);
    do
    {
        esi = port_u32(&port, ebp, -0x1cu);
        edi = port_u32(&port, ebp, -0x20u);
        port_call_with(&port, 0x487640, edi, 8, ebx, ecx, esi, edi, ebp);
        for (ecx = 0; ecx < 8;)
        {
            uint32_t entry_value =
                port_call_with(&port, 0x4877f0, esi, ecx, ebx, ecx, esi, edi, ebp);
            ebx = port_call_with(&port, 0x4831b0, entry_value, port_u32(&port, ebp, -0x18u), 0, ecx,
                                 esi, edi, ebp);
            result = port_call_with(&port, 0x487850, edi, ecx, ebx, ecx + 1, esi, edi, ebp);
            ecx++;
        }
        ebx = port_u32(&port, ebp, -0x20u) + 0x1c;
        esi = port_u32(&port, ebp, -0x1cu) + 0x1c;
        port_set32(&port, ebp, -0x20u, ebx);
        port_set32(&port, ebp, -0x1cu, esi);
    } while (esi != port_u32(&port, ebp, -0x24u));
    return port_return(&port, result, entry->edx);
}

/* Original 0x45f140: the eight entries of the resource row picked by the bytes 0x4fc050 (by ebx,
 * 28 a row from 0x544ac0) and 0x4fc058 (by edx, 24 an entry offset) take the name eax (0x482e10)
 * and the display 0x5b9c60 (0x483ed0). */
uint32_t vertrix_port_resource_indexed_finish_45f140(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x30
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t k;
    uint32_t index;
    uint32_t item;
    uint32_t ecx;
    uint32_t result = 0;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ecx);
    port_set32(&port, ebp, -8u, entry->esi);
    port_set32(&port, ebp, -0xcu, entry->edi);
    port_set32(&port, ebp, -0x10u, entry->eax);
    for (k = 0; k < 7; k++)
    {
        port_set8(&port, ebp - 0x2c + k, 0, port_u8(&port, 0x4fc050 + k, 0));
    }
    for (k = 0; k < 7; k++)
    {
        port_set8(&port, ebp - 0x24 + k, 0, port_u8(&port, 0x4fc058 + k, 0));
    }
    index = port_u8(&port, ebp - 0x24 + entry->edx, 0);
    port_set32(&port, ebp, -0x14u, index * 0x18);
    index = port_u8(&port, ebp - 0x2c + entry->ebx, 0);
    port_set32(&port, ebp, -0x18u, 0);
    port_set32(&port, ebp, -0x1cu, 0x544ac0 + index * 0x1c);
    for (k = 0; k < 8; k++)
    {
        uint32_t ebx = port_u32(&port, ebp, -0x18u);
        ecx = port_u32(&port, ebp, -0x14u);
        item = port_call_with(&port, 0x4877f0, port_u32(&port, ebp, -0x1cu), k, ebx, ecx,
                              index * 0x1c, k, ebp);
        port_call_with(&port, 0x482e10, item, port_u32(&port, ebp, -0x10u), ebx, ecx, item, k, ebp);
        ecx = port_u32(&port, ebp, -0x18u) + 0x18;
        result = port_call_with(&port, 0x483ed0, item, 0x5b9c60, ebx, ecx, item, k + 1, ebp);
        port_set32(&port, ebp, -0x18u, ecx);
    }
    return port_return(&port, result, vertrix_lift_edx);
}

/* Original 0x471100 (two stack arguments, the owner and the list): when 0x4126f0 lets the list
 * take the kind ecx, a companion actor (0x4ca000 of 0x15c bytes, 0x4abd70) is placed at the
 * signed words ax and dx (0x4710d0), added (0x4123d0) and marked (+0x110 1) when the kind is
 * the owner, and listed in 0x54671c (0x4b5e70). The actor, or 0. */
uint32_t vertrix_port_ui_companion_spawn_471100(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x18
    };
    Port port;
    uint8_t stack[BELOW + 8 + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t kind = entry->ecx;
    uint32_t owner;
    uint32_t list;
    uint32_t actor;
    uint32_t x;
    uint32_t y;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 2);
    owner = port_u32(&port, entry->esp, 4);
    list = port_u32(&port, entry->esp, 8);
    port_set16(&port, ebp, -0x10u, entry->eax);
    port_set16(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x14u, 0);
    if (port_call_with(&port, 0x4126f0, list, kind, entry->ebx, entry->ecx, entry->esi, kind,
                       ebp) != 1)
    {
        return port_return(&port, port_u32(&port, ebp, -0x14u), vertrix_lift_edx);
    }
    actor = port_call_with(&port, 0x4ca000, 0x15c, vertrix_lift_edx, entry->ebx, entry->ecx,
                           entry->esi, kind, ebp);
    if (actor != 0)
    {
        actor = port_call_with(&port, 0x4abd70, actor, vertrix_lift_edx, entry->ebx, entry->ecx,
                               entry->esi, kind, ebp);
    }
    y = (uint32_t)(int32_t)(int16_t)port_u16(&port, ebp, -0xcu);
    x = (uint32_t)(int32_t)(int16_t)port_u16(&port, ebp, -0x10u);
    port_set32(&port, ebp, -0x14u, actor);
    port_call_with(&port, 0x4710d0, actor, x, y, entry->ebx, actor, kind, ebp);
    port_call_with(&port, 0x4123d0, list, kind, actor, owner, actor, kind, ebp);
    if (kind == owner)
    {
        port_set8(&port, actor, 0x110, 1);
    }
    port_call_with(&port, 0x4b5e70, 0x54671c, port_u32(&port, ebp, -0x14u), actor, owner, actor,
                   kind, ebp);
    return port_return(&port, port_u32(&port, ebp, -0x14u), vertrix_lift_edx);
}

/* Original 0x4723a0 (one stack argument): a picture actor (0x4ca000 of 0x15c bytes, 0x4abd70)
 * set up by 0x4adf20 with zeros, kind 6, its picture made by 0x482f80 from eax, edx, ebx, ecx and
 * the argument, displayed on 0x5b9c60 (0x483ed0), taken (0x4ac950) and listed in 0x546780
 * (0x4b5e70). The actor. */
uint32_t vertrix_port_picture_actor_spawn_4723a0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x18
    };
    Port port;
    uint8_t stack[BELOW + 8 + 4];
    uint32_t ebp = entry->esp - 4;
    uint32_t width;
    uint32_t actor;
    uint32_t picture;
    uint32_t zeros[5] = {0, 0, 0, 0, 0};
    uint32_t pushed[11];
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 1);
    width = port_u32(&port, entry->esp, 4);
    port_set32(&port, ebp, -0xcu, entry->eax);
    port_set32(&port, ebp, -0x10u, entry->edx);
    port_set32(&port, ebp, -0x14u, entry->ebx);
    actor = call_frame(&port, 0x4ca000, 0x15c, entry->edx, entry->ebx, entry->ecx, entry->esi,
                       entry->ecx, ebp, NULL, 0);
    if (actor != 0)
    {
        actor = call_frame(&port, 0x4abd70, actor, vertrix_lift_edx, entry->ebx, entry->ecx,
                           entry->esi, entry->ecx, ebp, NULL, 0);
    }
    call_frame(&port, 0x4adf20, actor, 0, 0, 0, actor, entry->ecx, ebp, zeros, 5);
    pushed[0] = width;
    pushed[1] = 0;
    pushed[2] = 0;
    pushed[3] = 0;
    pushed[4] = 0;
    pushed[5] = entry->ecx;
    pushed[6] = width;
    pushed[7] = 0;
    pushed[8] = 0;
    pushed[9] = 0;
    pushed[10] = 4;
    port_set32(&port, actor, 0, 6);
    picture =
        call_frame(&port, 0x482f80, port_u32(&port, ebp, -0xcu), port_u32(&port, ebp, -0x10u),
                   port_u32(&port, ebp, -0x14u), entry->ecx, actor, entry->ecx, ebp, pushed, 11);
    call_frame(&port, 0x483ed0, picture, 0x5b9c60, port_u32(&port, ebp, -0x14u), picture, actor,
               entry->ecx, ebp, NULL, 0);
    call_frame(&port, 0x4ac950, actor, picture, port_u32(&port, ebp, -0x14u), picture, actor,
               entry->ecx, ebp, NULL, 0);
    call_frame(&port, 0x4b5e70, 0x546780, actor, port_u32(&port, ebp, -0x14u), picture, actor,
               entry->ecx, ebp, NULL, 0);
    return port_return(&port, actor, vertrix_lift_edx);
}

/* Original 0x477610: when the key text 0x556088 is not ready (0x4d66cd with 1) 0x556084 is
 * cleared (0x4ca070) and 0x4ec1f7 runs on 0x4feaad; with 0x553648 1 the byte dl is read into
 * 0x556084 (0x4cdad0, 0x4ca710) and its first byte pressed on 0x54d640 (0x476260). */
uint32_t vertrix_port_key_text_read_477610(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 8
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t result;
    uint32_t key;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -4u, entry->edx);
    result = port_forward(&port, entry, 0x4d66cd, 0x556088, 1, entry->ebx, entry->ecx);
    if (result == 0)
    {
        port_forward(&port, entry, 0x4ca070, 0x556084, vertrix_lift_edx, entry->ebx, entry->ecx);
        result = port_forward(&port, entry, 0x4ec1f7, 0x4feaad, vertrix_lift_edx, entry->ebx,
                              entry->ecx);
    }
    if (port_u32(&port, 0, 0x553648) != 1)
    {
        return port_return(&port, result, vertrix_lift_edx);
    }
    port_forward(&port, entry, 0x4cdad0, 0x556084, port_u8(&port, ebp, -4u), entry->ebx,
                 entry->ecx);
    port_forward(&port, entry, 0x4ca710, 0x556084, vertrix_lift_edx, entry->ebx, entry->ecx);
    key = port_u8(&port, port_u32(&port, 0, 0x556084), 0);
    port_set32(&port, ebp, -4u, key);
    result = port_forward(&port, entry, 0x476260, 0x54d640, key, 0, entry->ecx);
    return port_return(&port, result, vertrix_lift_edx);
}

/* Original 0x477e30: an object not yet placed (+0x60 0) takes its size (+0x48, +0x4a into +0x50,
 * +0x52), the middle of the screen (0x5b9c8e and 0x5b9c90 halved into +0x5c and +0x5e), +0x64 to
 * +0x70 0, +0x60 1, ebx (+0x54) and the margin edx (+0x58); 0x477d70 sizes it and 0x477e10 frames
 * the margin around the middle. */
uint32_t vertrix_port_object_center_place_477e30(PORT_SIGNATURE)
{
    Port port;
    uint32_t object = entry->eax;
    uint32_t margin = entry->edx;
    uint32_t placed;
    uint32_t left;
    uint32_t top;
    uint32_t pushed[1];
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    placed = port_u32(&port, object, 0x60);
    if (placed != 0)
    {
        return port_return(&port, object, placed);
    }
    port_set16(&port, object, 0x50, port_u16(&port, object, 0x48));
    port_set32(&port, object, 0x64, 0);
    port_set32(&port, object, 0x68, 0);
    port_set32(&port, object, 0x6c, 0);
    port_set32(&port, object, 0x70, 0);
    port_set16(&port, object, 0x52, port_u16(&port, object, 0x4a));
    port_set16(&port, object, 0x5c, port_u16(&port, 0, 0x5b9c8e) >> 1);
    port_set32(&port, object, 0x60, 1);
    port_set32(&port, object, 0x54, entry->ebx);
    port_set16(&port, object, 0x5e, port_u16(&port, 0, 0x5b9c90) >> 1);
    port_set32(&port, object, 0x58, margin);
    port_forward_esi(&port, entry, 0x477d70, object, 0, entry->ebx, margin, object);
    left = port_u16(&port, object, 0x5c) - margin;
    top = port_u16(&port, object, 0x5e) - margin;
    pushed[0] = (margin * 2 + top - 1) & 0xffff;
    result = port_call_registers(&port, 0x477e10, object, left & 0xffff, top & 0xffff,
                                 (left + margin * 2 - 1) & 0xffff, object, entry->edi, entry->ebp,
                                 pushed, 1);
    return port_return(&port, result, vertrix_lift_edx);
}

/* Original 0x47ea20: the display's two interfaces (+4, +8) released (their method +8) and
 * cleared. */
uint32_t vertrix_port_display_release_pair_47ea20(PORT_SIGNATURE)
{
    Port port;
    uint32_t display = entry->eax;
    uint32_t face;
    uint32_t eax = entry->eax;
    uint32_t pushed[1];
    port_open(&port, calls, services, globals, entry);
    face = port_u32(&port, display, 4);
    if (face != 0)
    {
        uint32_t methods = port_u32(&port, face, 0);
        pushed[0] = face;
        eax = call_frame(&port, port_u32(&port, methods, 8), face, methods, display, entry->ecx,
                         entry->esi, entry->edi, entry->ebp, pushed, 1);
        port_set32(&port, display, 4, 0);
    }
    face = port_u32(&port, display, 8);
    if (face != 0)
    {
        uint32_t methods = port_u32(&port, face, 0);
        pushed[0] = face;
        eax = call_frame(&port, port_u32(&port, methods, 8), eax, methods, display, face,
                         entry->esi, entry->edi, entry->ebp, pushed, 1);
        port_set32(&port, display, 8, 0);
    }
    return port_return(&port, eax, entry->edx);
}
