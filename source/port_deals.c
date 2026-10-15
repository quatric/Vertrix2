#include "port_deals.h"

/* The board's deal of a row of pieces. */

/* A row's offsets: the count routine, the kinds (13 bytes), the kinds beneath them and the
 * pieces (13 dwords). */
typedef struct Row
{
    uint32_t counter;
    uint32_t kinds;
    uint32_t below;
    uint32_t pieces;
} Row;

/* The deal of the row `row` of the board eax for the level edx and the turn ebx: with the turn
 * below 1 and the count (`counter`, then 0x417df0 of the level) over it, the board's pick (+0x1de)
 * is taken from its cells (0x4327e0 of +0x220, 0x41), and the 13 kinds of the row read from the
 * pattern 0x4f9ad8 at 13 times the level plus the turn: 2 is a bomb (5), 1 a kind drawn below 5
 * (0x4826c0 of 0x598d30) unlike the one left of it and the one beneath it, 0 none (0xff). With any
 * dealt, each kind has its piece made (0x430800, the state 0x44f700 by 0x4ac8f0, the speed
 * 0x4f9ad0 at 1 less the count plus the turn by 0x4ac7b0), the others cleared; 1, else 0. */
static uint32_t deal_row(PORT_SIGNATURE, const Row *row)
{
    enum
    {
        BELOW = 0x2c
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t board = entry->eax;
    uint32_t level = entry->edx;
    uint32_t turn = entry->ebx;
    uint32_t count;
    uint32_t dealt;
    uint32_t index;
    uint32_t place;
    uint32_t cell;
    uint32_t kind;
    uint32_t left;
    uint32_t under;
    uint32_t drawn;
    uint32_t piece;
    uint32_t speed;
    uint32_t edx;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t esi;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -4u, entry->ecx);
    port_set32(&port, ebp, -8u, entry->esi);
    port_set32(&port, ebp, -0xcu, entry->edi);
    port_set32(&port, ebp, -0x18u, board);
    port_set32(&port, ebp, -0x28u, turn);
    port_call_with(&port, row->counter, board, level, turn, level, entry->esi, entry->edi, ebp);
    count = port_call_with(&port, 0x417df0, level, 0, turn, level, entry->esi, entry->edi, ebp);
    dealt = vertrix_lift_edx;
    port_set32(&port, ebp, -0x20u, dealt);
    port_set32(&port, ebp, -0x1cu, count);
    if ((int32_t)turn >= 1 || count <= turn)
    {
        return port_return(&port, 0, dealt);
    }
    port_call_with(&port, 0x4327e0, board + 0x220, board + 0x1de, 0x41, level, entry->esi,
                   entry->edi, ebp);
    ecx = level * 13;
    place = turn * 13 + ecx;
    port_set32(&port, ebp, -0x10u, 0);
    port_set32(&port, ebp, -0x24u, place);
    edx = turn;
    ebx = 0x41;
    esi = entry->esi;
    for (index = 0; index < 13; ++index)
    {
        cell = board + index;
        kind = port_u8(&port, 0, place + index + 0x4f9ad8);
        if (kind == 2)
        {
            ++dealt;
            edx = dealt;
            port_set8(&port, cell, row->kinds, 5);
            port_set32(&port, ebp, -0x20u, dealt);
        }
        else if (kind == 1)
        {
            under = port_u8(&port, cell, row->below);
            left = index > 0 ? port_u8(&port, cell, row->kinds - 1) : 0xff;
            ebx = (ebx & 0xffff0000u) | (under << 8) | left;
            drawn = port_call_with(&port, 0x4826c0, 0x598d30, 5, ebx, ecx, esi, cell, ebp) & 0xff;
            edx = vertrix_lift_edx;
            esi = cell;
            ecx = cell;
            port_set8(&port, cell, row->kinds, drawn);
            while (port_u8(&port, cell, row->kinds) == left ||
                   port_u8(&port, cell, row->kinds) == under)
            {
                drawn =
                    port_call_with(&port, 0x4826c0, 0x598d30, 5, ebx, ecx, esi, cell, ebp) & 0xff;
                edx = vertrix_lift_edx;
                port_set8(&port, cell, row->kinds, drawn);
            }
            ++dealt;
            port_set32(&port, ebp, -0x20u, dealt);
        }
        else if (kind == 0)
        {
            port_set8(&port, cell, row->kinds, 0xff);
        }
        ebx = place + index + 1;
        esi = index + 1;
        port_set32(&port, ebp, -0x24u, ebx);
        port_set32(&port, ebp, -0x10u, esi);
    }
    if (dealt == 0)
    {
        return port_return(&port, 0, edx);
    }
    speed = turn + 1 - count;
    edx = speed;
    port_set32(&port, ebp, -0x14u, speed);
    for (index = 0; index < 13; ++index)
    {
        cell = board + index;
        ecx = board + index * 4;
        if (port_u8(&port, cell, row->kinds) == 0xff)
        {
            port_set32(&port, ecx, row->pieces, 0);
            continue;
        }
        piece = port_call_with(&port, 0x430800, board,
                               (uint32_t)(int32_t)(int8_t)port_u8(&port, cell, row->kinds),
                               board + 0x34, ecx, esi, cell, ebp);
        esi = piece;
        port_set32(&port, ecx, row->pieces, piece);
        port_call_with(&port, 0x4ac8f0, piece, 0x44f700, board + 0x34, ecx, piece, cell, ebp);
        port_call_with(&port, 0x4ac7b0, piece, port_u8(&port, 0, speed + 0x4f9ad0), board + 0x34,
                       ecx, piece, cell, ebp);
        edx = vertrix_lift_edx;
    }
    return port_return(&port, 1, edx);
}

/* Original 0x431780: the deal of the first row (0x42ec20; kinds +0x9da over +0x1de, pieces
 * +0x9e8). */
uint32_t vertrix_port_board_deal_first_row_431780(PORT_SIGNATURE)
{
    static const Row row = {0x42ec20, 0x9da, 0x1de, 0x9e8};
    return deal_row(calls, services, globals, entry, &row);
}

/* Original 0x431930: the deal of the second row (0x42ec40; kinds +0xa1c over +0x212, pieces
 * +0xa2c). */
uint32_t vertrix_port_board_deal_second_row_431930(PORT_SIGNATURE)
{
    static const Row row = {0x42ec40, 0xa1c, 0x212, 0xa2c};
    return deal_row(calls, services, globals, entry, &row);
}
