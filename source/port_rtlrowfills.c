#include "port_rtlrowfills.h"

/* Board rows filled from their patterns. */

/* Original 0x4314a0: the board eax's row for the column edx and the kind ebx (below 6), when
 * 0x417da0 of the column (after 0x42ec00) exceeds the kind: 0x4327e0 with +0x220, +0x1de, 0x41
 * and twice the column, then each of its five cells (+0x980, rows 0xd apart at +0x1ea) by the
 * pattern 0x4f9800 (30 per column, 5 per kind): 2 is a 5 (counted), 0 empty (0xff), 1 a gem
 * drawn from 0x598d30 (0x4826c0 below 5) and drawn again while it matches the cell before it (or
 * the row above when that is empty), the cell after when the pattern there is 0, or the row's own
 * +0x1ea (counted). With any counted (the count starting at 0x417da0's edx) each non-empty
 * cell's piece is made (0x430800), kept at +0x988 (else 0), stepped by 0x44f700 (0x4ac8f0) and
 * given 0x4f97f8's byte at 6 less the column count plus the kind (0x4ac7b0); eax 1, else 0. */
uint32_t vertrix_port_board_row_fill_4314a0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x40
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t board = entry->eax;
    uint32_t column = entry->edx;
    uint32_t kind = entry->ebx;
    uint32_t edx;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t height;
    uint32_t counted;
    uint32_t pattern;
    uint32_t next = 0;
    uint32_t index;
#define CALL(target, a, d) port_call_with(&port, target, a, d, ebx, ecx, esi, edi, ebp)
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ecx);
    port_set32(&port, ebp, -8u, entry->esi);
    port_set32(&port, ebp, -0xcu, entry->edi);
    port_set32(&port, ebp, -0x24u, board);
    port_set32(&port, ebp, -0x30u, kind);
    ebx = kind;
    ecx = column;
    CALL(0x42ec00, board, entry->edx);
    height = CALL(0x417da0, column, 0);
    edx = vertrix_lift_edx;
    counted = edx;
    port_set32(&port, ebp, -0x1cu, counted);
    port_set32(&port, ebp, -0x2cu, height);
    if ((int32_t)kind >= 6 || height <= kind)
    {
        return port_return(&port, 0, edx);
    }
    ebx = 0x41;
    ecx = column * 2;
    CALL(0x4327e0, board + 0x220, board + 0x1de);
    pattern = ecx * 15 + kind * 5;
    port_set32(&port, ebp, -0x38u, pattern);
    for (index = 0; index < 5 && !port.env.failed; index++)
    {
        uint32_t cell = board + index;
        uint32_t above = board - 0xd + 0xd * index;
        uint32_t below = board + 0xd + 0xd * index;
        uint32_t own = board + 0xd * index;
        uint32_t code;
        port_set32(&port, ebp, -0x18u, index);
        port_set32(&port, ebp, -0x28u, above);
        port_set32(&port, ebp, -0x20u, below);
        port_set32(&port, ebp, -0x34u, own);
        edi = cell;
        code = port_u8(&port, pattern + index, 0x4f9800);
        ecx = index;
        if (index < 4)
        {
            next = port_u8(&port, pattern + index, 0x4f9801);
            port_set8(&port, ebp, -0x10u, next);
        }
        if (code == 2)
        {
            counted++;
            port_set8(&port, cell, 0x980, 5);
        }
        else if (code == 1)
        {
            uint32_t before = 0xff;
            uint32_t after = 0xff;
            uint32_t self;
            uint32_t drawn;
            if (index != 0)
            {
                before = port_u8(&port, cell, 0x97f);
                if (before == 0xff)
                {
                    ebx = above;
                    before = port_u8(&port, above, 0x1ea);
                }
            }
            if (index < 4 && port_u8(&port, ebp, -0x10u) == 0)
            {
                after = port_u8(&port, below, 0x1ea);
            }
            self = port_u8(&port, own, 0x1ea);
            port_set8(&port, ebp, -0x14u, self);
            ebx = (ebx & 0xffff0000u) | (after << 8) | before;
            esi = cell;
            ecx = cell;
            port_set8(&port, cell, 0x980, CALL(0x4826c0, 0x598d30, 5));
            for (;;)
            {
                drawn = port_u8(&port, cell, 0x980);
                edx = (vertrix_lift_edx & 0xffffff00u) | drawn;
                if (port.env.failed || (before != drawn && after != drawn && drawn != self))
                {
                    break;
                }
                port_set8(&port, cell, 0x980, CALL(0x4826c0, 0x598d30, 5));
            }
            counted++;
        }
        else if (code == 0)
        {
            port_set8(&port, cell, 0x980, 0xff);
        }
        port_set32(&port, ebp, -0x1cu, counted);
        ebx = above + 0xd;
        esi = below + 0xd;
        edx = index + 1;
    }
    port_set32(&port, ebp, -0x18u, 5);
    port_set32(&port, ebp, -0x28u, board + 0xd * 4);
    port_set32(&port, ebp, -0x20u, board + 0xd * 6);
    port_set32(&port, ebp, -0x34u, board + 0xd * 5);
    if (counted == 0)
    {
        return port_return(&port, 0, edx);
    }
    ebx = 6 - height + kind;
    esi = height;
    port_set32(&port, ebp, -0x3cu, board + 0x14);
    for (index = 0; index < 5 && !port.env.failed; index++)
    {
        uint32_t piece = 0;
        uint32_t cell = board + index;
        ecx = board + index * 4;
        edi = cell;
        if (port_u8(&port, cell, 0x980) != 0xff)
        {
            edx = (uint32_t)(int32_t)(int8_t)port_u8(&port, cell, 0x980);
            piece = CALL(0x430800, board, edx);
            esi = piece;
            port_set32(&port, ecx, 0x988, piece);
            CALL(0x4ac8f0, piece, 0x44f700);
            edx = port_u8(&port, ebx, 0x4f97f8);
            CALL(0x4ac7b0, piece, edx);
            edx = vertrix_lift_edx;
        }
        else
        {
            port_set32(&port, ecx, 0x988, 0);
        }
    }
#undef CALL
    return port_return(&port, 1, edx);
}
