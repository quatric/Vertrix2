#include "port_rtldrains.h"

/* Choice picks, column copies, state drains, guarded loads and decimation. */

/* Original 0x429fe0: a random one (0x4826c0 of 0x598d30) of the rows 1..3 of the grid eax (four
 * dwords a row at +0x1cc) holding a 1, stored at edx and handed with its value to 0x42a080 (ebx
 * as given); 0 when none, edx then the last row's count. */
uint32_t vertrix_port_choice_grid_pick_cell_429fe0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x28
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t grid = entry->eax;
    uint32_t found = 0;
    uint32_t row;
    uint32_t ecx = 0;
    uint32_t edx = 0;
    uint32_t edi = entry->edi;
    uint32_t pick;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ecx);
    port_set32(&port, ebp, -8u, entry->esi);
    port_set32(&port, ebp, -0xcu, entry->edi);
    port_set32(&port, ebp, -0x14u, grid);
    port_set32(&port, ebp, -0x18u, entry->edx);
    port_set32(&port, ebp, -0x1cu, entry->ebx);
    port_set32(&port, ebp, -0x10u, grid + 0x20);
    for (row = 1; row < 4 && !port.env.failed; row++)
    {
        uint32_t place = (row << 4) + port_u32(&port, ebp, -0x14u);
        ecx = port_u32(&port, ebp, -0x10u);
        edx = 0;
        do
        {
            edi = port_u32(&port, place, 0x1cc);
            if (edi == 1)
            {
                edx += edi;
            }
            place += 4;
        } while (place != ecx && !port.env.failed);
        if (edx != 0)
        {
            found++;
            port_set8(&port, found + ebp, -0x25u, row);
        }
        port_set32(&port, ebp, -0x10u, port_u32(&port, ebp, -0x10u) + 0x10);
    }
    if (found == 0)
    {
        return port_return(&port, 0, edx);
    }
    pick = port_call_with(&port, 0x4826c0, 0x598d30, found & 0xffff, 4, ecx, found, edi, ebp);
    pick &= 0xffff;
    port_set8(&port, port_u32(&port, ebp, -0x18u), 0, port_u8(&port, pick + ebp, -0x24u));
    pick = port_call_with(&port, 0x42a080, port_u32(&port, ebp, -0x14u),
                          port_u8(&port, port_u32(&port, ebp, -0x18u), 0),
                          port_u32(&port, ebp, -0x1cu), ecx, found, edi, ebp);
    return port_return(&port, pick, vertrix_lift_edx);
}

/* Original 0x4bb3d0 (ret 4: rows): for each output row (the list ecx from its start, the input
 * list edx from index ebx), each of the decoder eax's +0x24 components' input row (+0x70 bytes)
 * spread into every +0x24th byte of the output row from the component's offset on. eax and edx
 * as the loops leave them (edx the row count less one, now negative). */
uint32_t vertrix_port_jpeg_rows_spread_4bb3d0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x24
    };
    Port port;
    uint8_t stack[BELOW + 8 + 4];
    uint32_t esp = entry->esp - BELOW;
    uint32_t components;
    uint32_t eax;
    uint32_t edx;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 1);
    port_set32(&port, esp, 0x20, entry->esi);
    port_set32(&port, esp, 0x1c, entry->edi);
    port_set32(&port, esp, 0x18, entry->ebp);
    port_set32(&port, esp, 0, entry->edx);
    port_set32(&port, esp, 4, entry->ebx);
    port_set32(&port, esp, 0x10, entry->ecx);
    components = port_u32(&port, entry->eax, 0x24);
    port_set32(&port, esp, 0x14, port_u32(&port, entry->eax, 0x70));
    eax = entry->ebx * 4;
    port_set32(&port, esp, 8, eax);
    for (;;)
    {
        uint32_t component = 0;
        edx = port_u32(&port, esp, 0x28) - 1;
        port_set32(&port, esp, 0x28, edx);
        if ((int32_t)edx < 0 || port.env.failed)
        {
            break;
        }
        if ((int32_t)components > 0)
        {
            uint32_t list = port_u32(&port, esp, 0);
            eax = port_u32(&port, esp, 8);
            port_set32(&port, esp, 0xc, eax);
            for (; (int32_t)component < (int32_t)components && !port.env.failed; component++)
            {
                uint32_t to;
                eax = port_u32(&port, list, 0) + port_u32(&port, esp, 0xc);
                to = port_u32(&port, port_u32(&port, esp, 0x10), 0) + component;
                edx = port_u32(&port, esp, 0x14);
                eax = port_u32(&port, eax, 0);
                while (edx != 0 && !port.env.failed)
                {
                    uint32_t c = port_u8(&port, eax, 0);
                    eax++;
                    edx--;
                    port_set8(&port, to, 0, c);
                    to += components;
                }
                list += 4;
            }
        }
        port_set32(&port, esp, 8, port_u32(&port, esp, 8) + 4);
        port_set32(&port, esp, 4, port_u32(&port, esp, 4) + 1);
        port_set32(&port, esp, 0x10, port_u32(&port, esp, 0x10) + 4);
    }
    return port_return(&port, eax, edx);
}

/* Original 0x451580: the player eax's piece +0x15c timed (0x4ac500, 0x4ac520); when the period is
 * up its steps (0x4ac540, 0x4ac5b0) each spend one of the pending drops (+0x838, 0x433840); with
 * drops left (or after) the piece's state handler +4 of +0x158 runs, and with none 0x433840,
 * 0x42eee0 with 0x451630, 0x4ac8f0 and the sound 0x43c0e0 of 0x4f81ac come first. edx kept. */
uint32_t vertrix_port_state_drain_451580(PORT_SIGNATURE)
{
    Port port;
    uint32_t player = entry->eax;
    uint32_t piece;
    uint32_t eax;
    uint32_t edx;
    uint32_t esi = entry->esi;
    port_open(&port, calls, services, globals, entry);
    piece = port_u32(&port, player, 0x15c);
    port_forward_esi(&port, entry, 0x4ac500, piece, entry->edx, player, piece, esi);
    eax = port_forward_esi(&port, entry, 0x4ac520, piece, vertrix_lift_edx, player, piece, esi);
    edx = vertrix_lift_edx;
    if (eax == 1)
    {
        esi = port_forward_esi(&port, entry, 0x4ac540, piece, edx, player, piece, esi);
        edx = esi;
        port_forward_esi(&port, entry, 0x4ac5b0, piece, edx, player, piece, esi);
        edx = vertrix_lift_edx;
        if (esi != 0)
        {
            do
            {
                if ((int32_t)port_u8(&port, piece, 0x838) > 0)
                {
                    port_forward_esi(&port, entry, 0x433840, piece, edx, player, piece, esi);
                    edx = vertrix_lift_edx;
                    port_set8(&port, piece, 0x838, port_u8(&port, piece, 0x838) - 1);
                }
                edx--;
            } while (edx != 0 && !port.env.failed);
        }
    }
    if (port_u8(&port, piece, 0x838) == 0)
    {
        port_forward_esi(&port, entry, 0x433840, piece, edx, player, piece, esi);
        port_forward_esi(&port, entry, 0x42eee0, piece, 0x451630, player, piece, esi);
        port_forward_esi(&port, entry, 0x4ac8f0, player, vertrix_lift_edx, player, piece, esi);
        port_forward_esi(&port, entry, 0x43c0e0, player, port_u32(&port, 0, 0x4f81ac), player,
                         piece, esi);
    }
    edx = port_u32(&port, piece, 0x158);
    eax = port_forward_esi(&port, entry, port_u32(&port, edx, 4), piece, edx, player, piece, esi);
    return port_return(&port, eax, entry->edx);
}

/* Original 0x45ac70: the actor eax's animation stepped (0x4ac370, 0x4ac390); when its period is up
 * its frames (0x4ac3b0, 0x4ac420) step by 0x4ac740 until 0x4ac780 reports the end, then 0x4ac4a0
 * and 0x4adfe0; at the end the next animation is chosen: its table entry +0x488 (0x540f88 by +4)
 * set (0x4ac8d0 with 0x544a34, 0x4ac710), the handler 0x45abd0 (0x4ac8a0), 0x4ac8f0 and 0x4adfe0.
 * eax as the last call leaves it, edx kept. */
uint32_t vertrix_port_actor_animation_step_45ac70(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t eax;
    uint32_t edx;
    uint32_t ebx = entry->ebx;
    uint32_t esi = 1;
    port_open(&port, calls, services, globals, entry);
    port_forward_esi(&port, entry, 0x4ac370, actor, entry->edx, ebx, actor, entry->esi);
    eax = port_forward_esi(&port, entry, 0x4ac390, actor, vertrix_lift_edx, ebx, actor, 1);
    if (eax != 1)
    {
        return port_return(&port, eax, entry->edx);
    }
    ebx = port_forward_esi(&port, entry, 0x4ac3b0, actor, vertrix_lift_edx, ebx, actor, esi);
    port_forward_esi(&port, entry, 0x4ac420, actor, ebx, ebx, actor, esi);
    edx = vertrix_lift_edx;
    if (ebx != 0)
    {
        do
        {
            if (port_forward_esi(&port, entry, 0x4ac780, actor, edx, ebx, actor, esi) != 0)
            {
                esi = 0;
                break;
            }
            edx = vertrix_lift_edx - 1;
            port_forward_esi(&port, entry, 0x4ac740, actor, edx, ebx, actor, esi);
            edx = vertrix_lift_edx;
        } while (edx != 0 && !port.env.failed);
    }
    port_forward_esi(&port, entry, 0x4ac4a0, actor, vertrix_lift_edx, ebx, actor, esi);
    eax = port_forward_esi(&port, entry, 0x4adfe0, actor, vertrix_lift_edx, ebx, actor, esi);
    if (esi != 0)
    {
        return port_return(&port, eax, entry->edx);
    }
    ebx = port_u32(&port, port_u32(&port, actor, 4) * 4, 0x540f88);
    ebx = port_u32(&port, ebx, 0x488);
    port_forward_esi(&port, entry, 0x4ac8d0, actor, 0x544a34, ebx, actor, esi);
    port_forward_esi(&port, entry, 0x4ac710, actor, ebx, ebx, actor, esi);
    port_forward_esi(&port, entry, 0x4ac8a0, actor, 0x45abd0, ebx, actor, esi);
    port_forward_esi(&port, entry, 0x4ac8f0, actor, vertrix_lift_edx, ebx, actor, esi);
    eax = port_forward_esi(&port, entry, 0x4adfe0, actor, vertrix_lift_edx, ebx, actor, esi);
    return port_return(&port, eax, entry->edx);
}

/* Original 0x473e60: under the guard record 0x5163d0 a 0x10-byte object (0x4ca000) made by
 * 0x488b10 with 1, given the name eax (0x489040); when that succeeds 0x473fc0 with edx and its
 * method +0x54; then the object destroyed (method +4 with 2). eax the restored chain. */
uint32_t vertrix_port_guarded_object_load_473e60(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x2c
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t record = ebp - 0x28;
    uint32_t name = entry->eax;
    uint32_t value = entry->edx;
    uint32_t object = 0;
    uint32_t esi = entry->edx;
    uint32_t memory;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->esi);
    port_set32(&port, ebp, -0x10u, entry->edi);
    port_set32(&port, record, 0, port.env.chain);
    port.env.chain = record;
    port_set32(&port, ebp, -0x24u, 0x4ec1ec);
    port_set32(&port, ebp, -0x20u, 0x5163d0);
    port_set32(&port, ebp, -0x1cu, 0);
    memory = port_call_with(&port, 0x4ca000, 0x10, 0x4ec1ec, 0, 0x5163d0, value, name, ebp);
    if (memory != 0)
    {
        port_set32(&port, ebp, -0x14u, memory);
        port_set32(&port, ebp, -0x1cu, 1);
        object = port_call_with(&port, 0x488b10, memory, 1, 0, 0x5163d0, value, name, ebp);
        port_set32(&port, ebp, -0x1cu, 0);
    }
    if (port_call_with(&port, 0x489040, object, name, object, object, value, name, ebp) == 1)
    {
        port_call_with(&port, 0x473fc0, object, value, object, object, value, name, ebp);
        esi = port_u32(&port, object, 0);
        port_call_with(&port, port_u32(&port, esi, 0x54), object, vertrix_lift_edx, object, object,
                       esi, name, ebp);
    }
    if (object != 0)
    {
        uint32_t methods = port_u32(&port, object, 0);
        port_call_with(&port, port_u32(&port, methods, 4), object, 2, object, methods, esi, name,
                       ebp);
    }
    port.env.chain = port_u32(&port, record, 0);
    return port_return(&port, port.env.chain, vertrix_lift_edx);
}

/* Original 0x47cd60: the 32-bit surface eax (format byte +0xc 4) decimated by ebx into the
 * dwords at edx: every ebx-th pixel of every ebx-th row, the width +4 and height +8 divided by
 * ebx (lift_div1, a zero divisor leaving them). The loop state lives in 0x558bf4..0x558c08. */
uint32_t vertrix_port_surface_decimate_47cd60(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x18
    };
    Port port;
    uint32_t esp = entry->esp - BELOW;
    uint32_t ecx;
    uint32_t esi;
    uint32_t edi;
    uint32_t ebp;
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    LiftFlags flags = {0};
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, esp, 0x14, entry->ecx);
    port_set32(&port, esp, 0x10, entry->esi);
    port_set32(&port, esp, 0xc, entry->edi);
    port_set32(&port, esp, 8, entry->ebp);
    ecx = port_u32(&port, 0, 0x558bfc);
    esi = port_u32(&port, 0, 0x558bf8);
    edi = port_u32(&port, 0, 0x558bf4);
    ebp = port_u32(&port, 0, 0x558c04);
    port_set32(&port, esp, 4, eax);
    port_set32(&port, esp, 0, edx);
    if (port_u8(&port, eax, 0xc) == 4)
    {
        eax = port_u32(&port, eax, 4);
        edx = (ebx - 1) * eax;
        port_set32(&port, 0, 0x558c08, edx);
        edx = 0;
        port_set32(&port, 0, 0x558c00, eax);
        lift_div1(32, ebx, &eax, &edx, &flags);
        ebp = port_u32(&port, port_u32(&port, esp, 4), 8);
        port_set32(&port, 0, 0x558c00, eax);
        edx = 0;
        eax = ebp;
        lift_div1(32, ebx, &eax, &edx, &flags);
        esi = port_u32(&port, port_u32(&port, esp, 4), 0);
        edi = port_u32(&port, esp, 0);
        ebp = eax;
        if (eax != 0)
        {
            ebx <<= 2;
            do
            {
                ecx = port_u32(&port, 0, 0x558c00);
                while (ecx != 0 && !port.env.failed)
                {
                    edi += 4;
                    edx = esi;
                    esi = port_u32(&port, esi, 0);
                    port_set32(&port, edi, -4u, esi);
                    esi = edx + ebx;
                    ecx--;
                }
                eax = port_u32(&port, 0, 0x558c08) << 2;
                esi += eax;
                ebp--;
            } while (ebp != 0 && !port.env.failed);
        }
    }
    port_set32(&port, 0, 0x558c04, ebp);
    port_set32(&port, 0, 0x558bf4, edi);
    port_set32(&port, 0, 0x558bf8, esi);
    port_set32(&port, 0, 0x558bfc, ecx);
    return port_return(&port, eax, edx);
}
