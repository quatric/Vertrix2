#include "port_rtltiles.h"

/* Board tile corners from their neighbours. */

/* Whether the grid cell `row`, `column` (13 a row from `grid`) is filled. */
static uint32_t filled(Port *port, uint32_t grid, uint32_t row, uint32_t column)
{
    return port_u8(port, grid + row * 0xd, column) != 0;
}

/* Original 0x433180: the corner tiles of the board eax's cell at the row dl (0..4) and column bl
 * (0..12) of the grid ecx: the neighbour flags 0x5407f9..0x540800 set (1 off the edge or when
 * filled): up-left, left, down-left, down, down-right, right, up-right and up; then the corners
 * from 0x4fb790 (left, up-left and up), 0x4fb798 (down, down-left, left), 0x4fb7a0 (up,
 * up-right, right) and 0x4fb7a8 (down-right, right, down), kept at +0x734..+0x737 (0x34 a row,
 * 4 a column) and at 0x540801..0x540804. eax the column; edx's low word the second and fourth
 * corners. */
uint32_t vertrix_port_board_tile_cell_433180(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 8
    };
    Port port;
    uint32_t board = entry->eax;
    uint32_t grid = entry->ecx;
    uint32_t row = entry->edx & 0xff;
    uint32_t column = entry->ebx & 0xff;
    uint32_t first;
    uint32_t second;
    uint32_t third;
    uint32_t fourth;
    uint32_t cell;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, entry->esp, -4u, entry->esi);
    port_set32(&port, entry->esp, -8u, entry->edi);
    port_set8(&port, 0, 0x5407f9,
              row == 0 || column == 0 || filled(&port, grid, row - 1, column - 1));
    port_set8(&port, 0, 0x5407fa, column == 0 || filled(&port, grid, row, column - 1));
    port_set8(&port, 0, 0x5407fb,
              row == 4 || column == 0 || filled(&port, grid, row + 1, column - 1));
    port_set8(&port, 0, 0x5407fc, row == 4 || filled(&port, grid, row + 1, column));
    port_set8(&port, 0, 0x5407fd,
              row == 4 || column == 0xc || filled(&port, grid, row + 1, column + 1));
    port_set8(&port, 0, 0x5407fe, column == 0xc || filled(&port, grid, row, column + 1));
    port_set8(&port, 0, 0x5407ff,
              row == 0 || column == 0xc || filled(&port, grid, row - 1, column + 1));
    port_set8(&port, 0, 0x540800, row == 0 || filled(&port, grid, row - 1, column));
    first = port_u8(&port, 0x4fb790,
                    (port_u8(&port, 0, 0x5407fa) + port_u8(&port, 0, 0x5407f9) * 2 +
                     port_u8(&port, 0, 0x540800) * 4) &
                        0xff);
    second = port_u8(&port, 0x4fb798,
                     (port_u8(&port, 0, 0x5407fc) + port_u8(&port, 0, 0x5407fb) * 2 +
                      port_u8(&port, 0, 0x5407fa) * 4) &
                         0xff);
    port_set8(&port, 0, 0x540803,
              port_u8(&port, 0, 0x540800) + port_u8(&port, 0, 0x5407ff) * 2 +
                  port_u8(&port, 0, 0x5407fe) * 4);
    third = port_u8(&port, 0x4fb7a0, port_u8(&port, 0, 0x540803));
    port_set8(&port, 0, 0x540803, third);
    port_set8(&port, 0, 0x540804,
              port_u8(&port, 0, 0x5407fd) * 2 + port_u8(&port, 0, 0x5407fe) +
                  port_u8(&port, 0, 0x5407fc) * 4);
    fourth = port_u8(&port, 0x4fb7a8, port_u8(&port, 0, 0x540804));
    port_set8(&port, 0, 0x540804, fourth);
    cell = board + row * 0x34 + column * 4;
    port_set8(&port, cell, 0x734, first);
    port_set8(&port, 0, 0x540802, second);
    port_set8(&port, cell, 0x735, second);
    port_set8(&port, cell, 0x736, port_u8(&port, 0, 0x540803));
    fourth = port_u8(&port, 0, 0x540804);
    port_set8(&port, 0, 0x540801, first);
    port_set8(&port, cell, 0x737, fourth);
    return port_return(&port, column, (entry->edx & 0xffff0000u) | (second << 8) | fourth);
}
