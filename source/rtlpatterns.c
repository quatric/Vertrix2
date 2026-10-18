#include "rtlpatterns.h"

/* Music pattern packing. */

/* Original 0x40f1a0: the eax rows of four-byte note cells packed into the header edx: +0 0, +2
 * the row count, +4 0x40, +6 the room (320 bytes a row) and +8 a buffer that big (0x4e7c90; 8
 * without), the cells copied after it at 64 a row (0x40c220) and packed in its start: each cell's
 * period (0x40f170 of its low 12 bits), instrument (high nibbles), effect and parameter; the
 * effects 0x100, 0x200, 0xa00, 0xe10, 0xe20, 0xea0 and 0xeb0 dropped, volume (8) parameters
 * doubled (0x80 and over as 0x80, exactly 0x80 as 0xff); a flag byte 0x80 with 1, 2, 8 and 0x10
 * for the parts present, then each present part's byte. +6 is cut to the packed length and the
 * buffer resized (0x4ec0e0; 8 on failure). eax 0 or 8. */
uint32_t vertrix_port_event_pack_40f1a0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x20
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t rows = entry->eax;
    uint32_t pack = entry->edx;
    uint32_t eax;
    uint32_t edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = rows;
    uint32_t esi = rows << 8;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->esi);
    port_set32(&port, ebp, -0x10u, entry->edi);
    port_set16(&port, pack, 0, 0);
    port_set16(&port, pack, 2, rows);
    port_set16(&port, pack, 4, 0x40);
    port_set16(&port, pack, 6, esi + (rows << 6));
    eax = port_call_with(&port, 0x4e7c90, port_u16(&port, pack, 6), pack, ebx, ecx, esi, pack, ebp);
    port_set32(&port, vertrix_lift_edx, 8, eax);
    eax = port_u32(&port, pack, 8);
    if (eax == 0)
    {
        return port_return(&port, 8, vertrix_lift_edx);
    }
    ebx = eax + (rows << 6);
    ecx = eax;
    eax = port_call_with(&port, 0x40c220, ebx, esi, ebx, ecx, esi, pack, ebp);
    edx = vertrix_lift_edx;
    while (esi != 0 && !port.env.failed)
    {
        uint32_t effect;
        edx = port_u8(&port, ebx, 1);
        eax = ((port_u8(&port, ebx, 0) & 0xf) << 8) + edx;
        eax = port_call_with(&port, 0x40f170, eax, edx, ebx, ecx, esi, pack, ebp);
        port_set32(&port, ebp, -0x18u, eax);
        eax = (port_u8(&port, ebx, 2) >> 4) & 0xf;
        edx = (port_u8(&port, ebx, 0) & 0xf0) + eax;
        port_set32(&port, ebp, -0x14u, edx);
        port_set32(&port, ebp, -0x1cu, port_u8(&port, ebx, 2) & 0xf);
        eax = port_u8(&port, ebx, 3);
        edx = (port_u32(&port, ebp, -0x1cu) << 8) + eax;
        ebx += 4;
        esi -= 4;
        effect = port_u32(&port, ebp, -0x1cu);
        if (edx == 0x100 || edx == 0x200 || edx == 0xa00 || edx == 0xe10 || edx == 0xe20 ||
            edx == 0xea0 || edx == 0xeb0)
        {
            eax = 0;
            port_set32(&port, ebp, -0x1cu, 0);
        }
        else if (effect == 8)
        {
            if (eax > 0x80)
            {
                eax = 0x80;
            }
            else if (eax < 0x80)
            {
                eax += eax;
            }
            else
            {
                eax = 0xff;
            }
        }
        edx = port_u32(&port, ebp, -0x18u) != 0 ? 0x81 : 0x80;
        if (port_u32(&port, ebp, -0x14u) != 0)
        {
            edx |= 2;
        }
        if (port_u32(&port, ebp, -0x1cu) != 0)
        {
            edx |= 8;
        }
        if (eax != 0)
        {
            edx |= 0x10;
        }
        port_set8(&port, ecx, 0, edx);
        ecx++;
        if (port_u32(&port, ebp, -0x18u) != 0)
        {
            edx = (edx & 0xffffff00u) | port_u8(&port, ebp, -0x18u);
            port_set8(&port, ecx, 0, edx);
            ecx++;
        }
        if (port_u32(&port, ebp, -0x14u) != 0)
        {
            edx = (edx & 0xffffff00u) | port_u8(&port, ebp, -0x14u);
            port_set8(&port, ecx, 0, edx);
            ecx++;
        }
        if (port_u32(&port, ebp, -0x1cu) != 0)
        {
            edx = (edx & 0xffffff00u) | port_u8(&port, ebp, -0x1cu);
            port_set8(&port, ecx, 0, edx);
            ecx++;
        }
        if (eax != 0)
        {
            port_set8(&port, ecx, 0, eax);
            ecx++;
        }
    }
    eax = (eax & 0xffff0000u) | port_u16(&port, pack, 8);
    ecx -= eax;
    port_set16(&port, pack, 6, ecx);
    eax = port_call_with(&port, 0x4ec0e0, port_u32(&port, pack, 8), ecx & 0xffff, ebx, ecx, esi,
                         pack, ebp);
    port_set32(&port, pack, 8, eax);
    return port_return(&port, eax == 0 ? 8 : 0, vertrix_lift_edx);
}

/* The marks of a blast of the kind on the 5 by 13 byte board: a 5 by 13 table of ints at ebp -
 * 0x144 cleared (0x432840 with 0x68); for each cell holding 6 the kinds 1, 3 and 4 mark its
 * column, 2, 3 and 4 its row, and 4 the rows either side. */
static void blast_marks(Port *port, const LiftEntry *entry, uint32_t board, uint32_t edx,
                        uint32_t ebx, uint32_t kind)
{
    uint32_t ebp = entry->esp - 4;
    uint32_t table = ebp - 0x144;
    uint32_t row;
    uint32_t column;
    uint32_t i;
    port_call_with(port, 0x432840, table, edx, ebx, 0x68, entry->esi, entry->edi, ebp);
    for (row = 0; row < 5 && !port->env.failed; row++)
    {
        for (column = 0; column < 13; column++)
        {
            if (port_u8(port, board + row * 13 + column, 0) != 6)
            {
                continue;
            }
            if (kind == 1 || kind == 3 || kind == 4)
            {
                for (i = 0; i < 5; i++)
                {
                    port_set32(port, table, i * 0x34 + column * 4, 1);
                }
            }
            if (kind == 2 || kind == 3 || kind == 4)
            {
                for (i = 0; i < 13; i++)
                {
                    port_set32(port, table, row * 0x34 + i * 4, 1);
                }
            }
            if (kind == 4)
            {
                if (row > 0)
                {
                    for (i = 0; i < 13; i++)
                    {
                        port_set32(port, table, (row - 1) * 0x34 + i * 4, 1);
                    }
                }
                if (row < 4)
                {
                    for (i = 0; i < 13; i++)
                    {
                        port_set32(port, table, (row + 1) * 0x34 + i * 4, 1);
                    }
                }
            }
        }
    }
}

/* Original 0x4344e0: the cells a blast of the kind bl hits on the board eax (blast_marks) counted
 * into *edx: the marked cells not holding 0xff. eax 0x138, edx the board end. */
uint32_t vertrix_port_board_blast_count_4344e0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x148
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t board = entry->eax;
    uint32_t total = entry->edx;
    uint32_t table = ebp - 0x144;
    uint32_t row;
    uint32_t eax = 0;
    uint32_t edx = 0;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ecx);
    port_set32(&port, ebp, -8u, entry->esi);
    port_set32(&port, ebp, -0xcu, entry->edi);
    port_set32(&port, ebp, -0x2cu, board);
    port_set32(&port, ebp, -0x1cu, total);
    port_set8(&port, ebp, -0x10u, entry->ebx);
    port_set32(&port, total, 0, 0);
    blast_marks(&port, entry, board, total, entry->ebx, entry->ebx & 0xff);
    for (row = 0; row < 5; row++)
    {
        edx = board + row * 13;
        for (eax = row * 0x34; eax != (row + 1) * 0x34; eax += 4)
        {
            if (port_u32(&port, table, eax) == 1 && port_u8(&port, edx, 0) != 0xff)
            {
                port_set32(&port, total, 0, port_u32(&port, total, 0) + 1);
            }
            edx++;
        }
        eax = (row + 1) * 0x34 + 0x34;
    }
    return port_return(&port, eax, edx);
}

/* Original 0x434300: the cells a blast of the kind cl hits on the board eax (blast_marks): *ebx
 * counts the marked cells not holding 0xff and *edx those of them holding 5. eax 13, edx 0x104.
 */
uint32_t vertrix_port_board_blast_tally_434300(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x148
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t board = entry->eax;
    uint32_t fives = entry->edx;
    uint32_t total = entry->ebx;
    uint32_t table = ebp - 0x144;
    uint32_t row;
    uint32_t eax = 0;
    uint32_t edx = 0;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->esi);
    port_set32(&port, ebp, -8u, entry->edi);
    port_set32(&port, ebp, -0x40u, board);
    port_set32(&port, ebp, -0x18u, fives);
    port_set32(&port, ebp, -0x14u, total);
    port_set8(&port, ebp, -0xcu, entry->ecx);
    port_set32(&port, fives, 0, 0);
    port_set32(&port, total, 0, 0);
    blast_marks(&port, entry, board, fives, total, entry->ecx & 0xff);
    for (row = 0; row < 5; row++)
    {
        edx = row * 0x34;
        for (eax = 0; eax < 13; eax++)
        {
            uint32_t cell = board + row * 13 + eax;
            if (port_u32(&port, table, edx) == 1 && port_u8(&port, cell, 0) != 0xff)
            {
                port_set32(&port, total, 0, port_u32(&port, total, 0) + 1);
                if (port_u8(&port, cell, 0) == 5)
                {
                    port_set32(&port, fives, 0, port_u32(&port, fives, 0) + 1);
                }
            }
            edx += 4;
        }
    }
    return port_return(&port, eax, edx);
}
/* Original 0x418af0: the game eax loaded with a progress step (0x418270 with 1) between parts:
 * with no +0xd8 its levels made (0x415db0), else the step 0x4c; the backdrop named by 0x4fc5a8
 * with the language name 0x513c21 (0x45f540) loaded (0x4816f0 with 0), shown (0x441f20) and
 * released (0x478d80); both tune players 0x598d30 and 0x598d48 stopped (0x482720) and rewound
 * (0x482550) with +4 cleared; the timer 0x4b7da0 started if idle (0x4b7cd0, 0x4b7c00); the
 * sounds 0x5536c8 and 0x553798 loaded for it (0x476a00 with 0 and 1, 0x476d20 when new); the
 * actors 0x5588f8 loaded (0x477af0; 0 ends), cleared (0x477d70), 0x532b64 kept at 0x55893c; the
 * fonts 0x55608c (0x4772f0; 0 ends), the keys 0x54d640 reset, the board 0x5b9c60 made (0x441e30,
 * 0x474e00) and 0x45dca0. eax the last answer, edx kept. */
uint32_t vertrix_port_game_load_418af0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x118
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t game = entry->eax;
    uint32_t eax;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
#define CALL(target, a, d) port_call_with(&port, target, a, d, ebx, ecx, game, entry->edi, ebp)
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    if (port_u32(&port, game, 0xd8) == 0)
    {
        CALL(0x415db0, game, entry->edx);
    }
    else
    {
        CALL(0x418270, 0x4c, entry->edx);
    }
    ebx = port_u32(&port, port_u8(&port, 0, 0x513c21) * 4 + 0x5334a0, 0);
    CALL(0x45f540, ebp - 0x114, 0x4fc5a8);
    eax = CALL(0x4816f0, ebp - 0x114, 0);
    CALL(0x441f20, eax, eax);
    CALL(0x478d80, vertrix_lift_edx, vertrix_lift_edx);
    CALL(0x418270, 1, vertrix_lift_edx);
    CALL(0x482720, 0x598d30, vertrix_lift_edx);
    CALL(0x482550, 0x598d30, vertrix_lift_edx);
    port_set8(&port, 0, 0x598d34, 0);
    CALL(0x482720, 0x598d48, vertrix_lift_edx);
    CALL(0x482550, 0x598d48, vertrix_lift_edx & 0xffffff00u);
    port_set8(&port, 0, 0x598d4c, vertrix_lift_edx);
    eax = CALL(0x418270, 1, vertrix_lift_edx);
    eax = CALL(0x4b7da0, eax, vertrix_lift_edx);
    if (eax == 0)
    {
        eax = CALL(0x4b7cd0, eax, vertrix_lift_edx);
        CALL(0x4b7c00, eax, vertrix_lift_edx);
    }
    ecx = 0;
    ebx = 0;
    eax = CALL(0x476a00, 0x5536c8, game);
    if (eax == 1)
    {
        CALL(0x476d20, 0x5536c8, vertrix_lift_edx);
    }
    ecx = 1;
    eax = CALL(0x476a00, 0x553798, game);
    if (eax == 1)
    {
        CALL(0x476d20, 0x553798, vertrix_lift_edx);
    }
    CALL(0x418270, 1, vertrix_lift_edx);
    eax = CALL(0x477af0, 0x5588f8, game);
    if (eax == 0)
    {
        return port_return(&port, eax, entry->edx);
    }
    CALL(0x477d70, 0x5588f8, vertrix_lift_edx);
    port_set32(&port, 0, 0x55893c, port_u32(&port, 0, 0x532b64));
    CALL(0x418270, 1, game);
    eax = CALL(0x4772f0, 0x55608c, vertrix_lift_edx);
    if (eax == 0)
    {
        return port_return(&port, eax, entry->edx);
    }
    CALL(0x418270, 1, vertrix_lift_edx);
    CALL(0x476090, 0x54d640, vertrix_lift_edx);
    CALL(0x4760c0, 0x54d640, vertrix_lift_edx);
    CALL(0x476590, 0x54d640, vertrix_lift_edx);
    CALL(0x4765b0, 0x54d640, 1);
    CALL(0x476140, 0x54d640, vertrix_lift_edx);
    CALL(0x418270, 1, vertrix_lift_edx);
    CALL(0x441e30, 0x5b9c60, vertrix_lift_edx);
    CALL(0x418270, 1, vertrix_lift_edx);
    CALL(0x474e00, 0x5b9c60, vertrix_lift_edx);
    eax = CALL(0x418270, 1, vertrix_lift_edx);
    eax = CALL(0x45dca0, eax, vertrix_lift_edx);
#undef CALL
    return port_return(&port, eax, entry->edx);
}

/* Original 0x441b70 (guarded 0x51506c): the backdrop view eax given the picture edx inside the
 * block at ebp - 0x138 (0x48a620, closed by 0x48a670): its +0x268 the picture and +0x26c..+0x278
 * cleared; unless its name +0x104 is 0x50e13d (0x489d00) its two layers loaded (0x4816f0 with 0
 * into +0x274 and +0x278); its size +0x208/+0x20c from the picture's +4/+8, the view kept at
 * 0x544070, +0x220 and +0x222 0, its scroll range +0x210/+0x212 the size less the screen
 * 0x5b9c8e/0x5b9c90 (0 when not above), +0x214 and +0x216 0, its shown size +0x218/+0x21a the
 * smaller of the two, +0x21c and +0x21e 1, +0x226 and +0x228 0. eax the restored chain. */
uint32_t vertrix_port_backdrop_view_set_441b70(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x13c
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t record = ebp - 0x24;
    uint32_t view = entry->eax;
    uint32_t eax;
    uint32_t edx;
    uint32_t ebx = 0x4ec1ec;
    uint32_t ecx = view;
    uint32_t esi = 0x51506c;
#define CALL(target, a, d) port_call_with(&port, target, a, d, ebx, ecx, esi, 0, ebp)
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->esi);
    port_set32(&port, ebp, -0x10u, entry->edi);
    port_set32(&port, record, 0, port.env.chain);
    port.env.chain = record;
    port_set32(&port, ebp, -0x20u, 0x4ec1ec);
    port_set32(&port, ebp, -0x1cu, 0x51506c);
    port_set32(&port, ebp, -0x18u, 0);
    CALL(0x48a620, ebp - 0x138, entry->edx);
    edx = vertrix_lift_edx;
    port_set32(&port, ebp, -0x18u, 1);
    port_set32(&port, view, 0x268, 0);
    port_set32(&port, view, 0x274, 0);
    port_set32(&port, view, 0x278, 0);
    port_set32(&port, view, 0x270, 0);
    port_set32(&port, view, 0x26c, 0);
    port_set32(&port, view, 0x268, edx);
    if (edx == 0)
    {
        CALL(0x48a670, ebp - 0x138, edx);
        eax = port_u32(&port, record, 0);
        port.env.chain = eax;
        return port_return(&port, eax, vertrix_lift_edx);
    }
    ebx = view + 0x104;
    eax = CALL(0x489d00, ebx, 0x50e13d);
    edx = vertrix_lift_edx;
    if (eax == 0)
    {
        eax = CALL(0x4816f0, ebx, 0);
        port_set32(&port, view, 0x274, eax);
        eax = CALL(0x4816f0, ebx, 0);
        port_set32(&port, view, 0x278, eax);
        edx = vertrix_lift_edx;
    }
    port_set32(&port, view, 0x208, port_u32(&port, port_u32(&port, view, 0x268), 4));
    port_set32(&port, view, 0x20c, port_u32(&port, port_u32(&port, view, 0x268), 8));
    edx = (edx & 0xffff0000u) | port_u16(&port, 0, 0x5b9c8e);
    eax = port_u32(&port, port_u32(&port, view, 0x268), 8);
    eax = (eax & 0xffff0000u) | port_u16(&port, view, 0x208);
    port_set32(&port, 0, 0x544070, view);
    eax -= edx;
    port_set8(&port, view, 0x220, 0);
    port_set8(&port, view, 0x222, 0);
    if ((int16_t)eax <= 0)
    {
        eax = 0;
    }
    port_set16(&port, view, 0x210, eax);
    ebx = (ebx & 0xffff0000u) | port_u16(&port, 0, 0x5b9c90);
    eax = (eax & 0xffff0000u) | port_u16(&port, view, 0x20c);
    eax -= ebx;
    if ((int16_t)eax <= 0)
    {
        eax = 0;
    }
    port_set16(&port, view, 0x214, 0);
    port_set16(&port, view, 0x212, eax);
    edx = port_u16(&port, 0, 0x5b9c8e);
    eax = (eax & 0xffff0000u) | port_u16(&port, view, 0x208);
    port_set16(&port, view, 0x216, 0);
    if ((int32_t)(int16_t)eax >= (int32_t)edx)
    {
        eax = edx;
    }
    port_set16(&port, view, 0x218, eax);
    ebx = port_u16(&port, 0, 0x5b9c90);
    eax = (eax & 0xffff0000u) | port_u16(&port, view, 0x20c);
    if ((int32_t)(int16_t)eax >= (int32_t)ebx)
    {
        eax = ebx;
    }
    port_set16(&port, view, 0x21c, 1);
    port_set16(&port, view, 0x21e, 1);
    port_set16(&port, view, 0x226, 0);
    port_set8(&port, view, 0x228, 0);
    port_set16(&port, view, 0x21a, eax);
    ecx = 0;
    port_set32(&port, ebp, -0x18u, 0);
    CALL(0x48a670, ebp - 0x138, 0);
#undef CALL
    port_set32(&port, ebp, -0x18u, 0);
    eax = port_u32(&port, record, 0);
    port.env.chain = eax;
    return port_return(&port, eax, vertrix_lift_edx);
}
