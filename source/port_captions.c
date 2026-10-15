#include "port_captions.h"

/* The text table's refresh for the language. */

/* Original 0x415180: the text table 0x53bdfc (20 rows of 9 texts) is set (0x4ca310) from the
 * language eax's block 0x53c0cc (80 bytes a language, 4 a row, 0xf0 a text); its rows 1 to 6
 * then from the set edx's block 0x53c93c (24 bytes a set, 4 a row, 0x1c8 a text). Each row's
 * count past its last text not 0x50d383 (0x4ccfe0) goes to 0x53bd0c, and its count and total
 * length of texts that are 0x50d384 to 0x53bd5c and 0x53bdac. */
uint32_t vertrix_port_text_table_refresh_415180(PORT_SIGNATURE)
{
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t language = entry->eax * 0x50;
    uint32_t set = entry->edx * 0x18;
    uint32_t row;
    uint32_t text;
    uint32_t place;
    uint32_t count;
    uint32_t length;
    int32_t last;
    port_open(&port, calls, services, globals, entry);
    for (row = 0; row < 0x14; ++row)
    {
        for (text = 0; text < 9; ++text)
        {
            place = 0x53bdfc + row * 0x24 + text * 4;
            port_call_with(&port, 0x4ca310, place, 0x53c0cc + language + row * 4 + text * 0xf0,
                           0x53c0cc + language + row * 4 + text * 0xf0, place,
                           0x53bdfc + (row + 1) * 0x24, row, ebp);
        }
    }
    for (row = 0; row < 6; ++row)
    {
        for (text = 0; text < 9; ++text)
        {
            place = 0x53bdfc + (row + 1) * 0x24 + text * 4;
            port_call_with(&port, 0x4ca310, place, 0x53c93c + set + row * 4 + text * 0x1c8,
                           0x53c93c + set + row * 4 + text * 0x1c8, place,
                           0x53bdfc + (row + 2) * 0x24, row, ebp);
        }
    }
    for (row = 0; row < 0x14; ++row)
    {
        for (last = 8; last >= 0; --last)
        {
            place = 0x53bdfc + row * 0x24 + (uint32_t)last * 4;
            if (port_call_with(&port, 0x4ccfe0, port_u32(&port, place, 0), 0x50d383, (uint32_t)last,
                               place, (uint32_t)last + 1, row * 4, ebp) != 0)
            {
                break;
            }
        }
        port_set32(&port, 0, 0x53bd0c + row * 4, (uint32_t)(last + 1));
    }
    for (row = 0; row < 0x14; ++row)
    {
        count = 0;
        length = 0;
        for (text = 0; text < 9; ++text)
        {
            place = 0x53bdfc + row * 0x24 + text * 4;
            if (port_call_with(&port, 0x4ccfe0, port_u32(&port, place, 0), 0x50d384, place, text,
                               length, count, ebp) != 0)
            {
                ++count;
                length += port_u32(&port, port_u32(&port, place, 0) - 0xc, 4);
            }
        }
        port_set32(&port, 0, 0x53bd5c + row * 4, count);
        port_set32(&port, 0, 0x53bdac + row * 4, length);
    }
    return port_return(&port, 0x4c, vertrix_lift_edx);
}
