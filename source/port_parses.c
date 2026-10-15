#include "port_parses.h"

/* The table read from a text stream. */

/* Original 0x48a100: the table eax read from the stream edx (guarded 0x5175c8, the token at
 * ebp-0x28 made by 0x4ca070): the table is cleared (0x48a2d0); until the stream is done
 * (0x48a910) after its blanks (0x48a310), each line's tokens (0x48a3c0, copied by 0x4ca090 and
 * released by 0x4ca210) go into a new list (0x4ca000 of 0x14 bytes, 0x4b7600 with 2 and 1;
 * 0x4b76d0) while a token follows on the line (0x48a420), and the list joins the table
 * (0x4b79a0) when it holds any (+8), else is destroyed (method +4 with 2). Then every text of
 * every row (0x48a2e0, 0x48a2f0) is read once (0x48a300 into ebp-0x1c, released). Returns 1 when
 * the table has rows, else 0; ebx and ecx carried between the calls as the original leaves them. */
uint32_t vertrix_port_table_read_48a100(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x40
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t table = entry->eax;
    uint32_t stream = entry->edx;
    uint32_t ebx = 0;
    uint32_t ecx = 0x5175c8;
    uint32_t list;
    uint32_t text;
    uint32_t row;
    uint32_t column;
    uint32_t result;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->esi);
    port_set32(&port, ebp, -0x10u, entry->edi);
    port_set32(&port, ebp, -0x3cu, port.env.chain);
    port_set32(&port, ebp, -0x38u, 0x4ec1ec);
    port_set32(&port, ebp, -0x34u, 0x5175c8);
    port_set32(&port, ebp, -0x30u, 0);
    port_call_with(&port, 0x4ca070, ebp - 0x28, 0x4ec1ec, ebx, ecx, table, stream, ebp);
    port_set32(&port, ebp, -0x30u, 1);
    port_call_with(&port, 0x48a2d0, table, vertrix_lift_edx, ebx, ecx, table, stream, ebp);
    for (;;)
    {
        port_call_with(&port, 0x48a310, table, stream, ebx, ecx, table, stream, ebp);
        if (port_call_with(&port, 0x48a910, stream, vertrix_lift_edx, ebx, ecx, table, stream,
                           ebp) != 0)
        {
            break;
        }
        list =
            port_call_with(&port, 0x4ca000, 0x14, vertrix_lift_edx, ebx, ecx, table, stream, ebp);
        if (list != 0)
        {
            port_set32(&port, ebp, -0x24u, list);
            port_set32(&port, ebp, -0x30u, 2);
            ecx = 1;
            list = port_call_with(&port, 0x4b7600, list, 2, ebx, ecx, table, stream, ebp);
            port_set32(&port, ebp, -0x30u, ecx);
        }
        ecx = list;
        port_set32(&port, ebp, -0x14u, 1);
        do
        {
            port_call_with(&port, 0x48a3c0, table, stream, ebp - 0x28, ecx, table, stream, ebp);
            text = port_call_with(&port, 0x4ca090, ebp - 0x20, ebp - 0x28, ebp - 0x28, ecx, table,
                                  stream, ebp);
            port_set32(&port, ebp, -0x30u, 4);
            ebx = 1;
            port_call_with(&port, 0x4b76d0, ecx, text, ebx, ecx, table, stream, ebp);
            port_set32(&port, ebp, -0x30u, ebx);
            port_call_with(&port, 0x4ca210, ebp - 0x20, 0, ebx, ecx, table, stream, ebp);
            port_set32(&port, ebp, -0x30u, ebx);
            if (port_call_with(&port, 0x48a420, table, stream, ebx, ecx, table, stream, ebp) == 0)
            {
                port_set32(&port, ebp, -0x14u, 0);
            }
            ebx = 1;
            port_set32(&port, ebp, -0x30u, ebx);
        } while (port_u32(&port, ebp, -0x14u) != 0 && !port.env.failed);
        if ((int32_t)port_u32(&port, ecx, 8) > 0)
        {
            port_call_with(&port, 0x4b79a0, table, ecx, ebx, ecx, table, stream, ebp);
        }
        else if (ecx != 0)
        {
            ebx = port_u32(&port, ecx, 0);
            port_call_with(&port, port_u32(&port, ebx, 4), ecx, 2, ebx, ecx, table, stream, ebp);
        }
        port_set32(&port, ebp, -0x30u, 1);
        if (port.env.failed)
        {
            break;
        }
    }
    port_set32(&port, ebp, -0x18u, 0);
    for (;;)
    {
        ecx = port_u32(&port, ebp, -0x18u);
        if (port_call_with(&port, 0x48a2e0, table, vertrix_lift_edx, ebx, ecx, table, 0, ebp) <=
                ecx ||
            port.env.failed)
        {
            break;
        }
        row = port_u32(&port, ebp, -0x18u);
        for (column = 0;
             column < port_call_with(&port, 0x48a2f0, table, row, ebx, ecx, table, column, ebp);
             column++)
        {
            ebx = row;
            ecx = column;
            port_call_with(&port, 0x48a300, table, ebp - 0x1c, ebx, ecx, table, column, ebp);
            port_set32(&port, ebp, -0x30u, 1);
            port_call_with(&port, 0x4ca210, ebp - 0x1c, 0, ebx, ecx, table, column, ebp);
            port_set32(&port, ebp, -0x30u, 1);
            if (port.env.failed)
            {
                break;
            }
            row = port_u32(&port, ebp, -0x18u);
        }
        port_set32(&port, ebp, -0x18u, port_u32(&port, ebp, -0x18u) + 1);
    }
    result = port_call_with(&port, 0x48a2e0, table, vertrix_lift_edx, ebx, ecx, table, 0, ebp) != 0;
    port_call_with(&port, 0x4ca210, ebp - 0x28, 0, ebx, ecx, table, result, ebp);
    return port_return(&port, result, vertrix_lift_edx);
}
