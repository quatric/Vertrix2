#include "rtlvolumecolumns.h"

/* Music volume column effects. */

/* Original 0x40dc80: the volume column byte +2 of the channel eax, by the tick 0x531b4c (0 the
 * first): 0x10..0x50 on the first tick set the volume +0x10/+0x14 to it less 0x10; after the
 * first tick 0x6x/0x7x slide it down/up by x (0 to 0x40); on the first tick 0x8x/0x9x do so
 * finely, 0xax sets the vibrato speed +0x48 to 4x and 0xbx its depth +0x44 to x (each when x is
 * not 0), and 0xcx sets the panning +0x1c to 16x; after it 0xbx vibrates (0x40d090), 0xdx/0xex
 * slide the panning left/right by x (0 to 0xff) and 0xfx slides to the note (0x40cff0). A volume
 * change marks +1 with 2, a panning change with 4. eax the value last worked on, edx kept. */
uint32_t vertrix_port_mixer_volume_column_40dc80(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x14
    };
    Port port;
    uint32_t channel = entry->eax;
    uint32_t value;
    uint32_t amount;
    int first;
    int32_t level;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, entry->esp, -4u, entry->ebx);
    port_set32(&port, entry->esp, -8u, entry->ecx);
    port_set32(&port, entry->esp, -0xcu, entry->edx);
    port_set32(&port, entry->esp, -0x10u, entry->esi);
    port_set32(&port, entry->esp, -0x14u, entry->edi);
    value = port_u8(&port, channel, 2);
    amount = value & 0xf;
    first = port_u32(&port, 0, 0x531b4c) == 0;
    if (value >= 0x10 && value <= 0x50)
    {
        if (first)
        {
            value -= 0x10;
            port_set32(&port, channel, 0x10, value);
            port_set32(&port, channel, 0x14, value);
            port_set8(&port, channel, 1, port_u8(&port, channel, 1) | 2);
        }
    }
    else if (value >= 0x60 && value <= 0x9f)
    {
        int fine = value >= 0x80;
        if (first == fine)
        {
            level = (int32_t)port_u32(&port, channel, 0x10);
            if (value < 0x70 || (value >= 0x80 && value < 0x90))
            {
                level -= (int32_t)amount;
                port_set32(&port, channel, 0x10, (uint32_t)level);
                if (level < 0)
                {
                    port_set32(&port, channel, 0x10, 0);
                }
            }
            else
            {
                level += (int32_t)amount;
                port_set32(&port, channel, 0x10, (uint32_t)level);
                if (level > 0x40)
                {
                    port_set32(&port, channel, 0x10, 0x40);
                }
            }
            value = port_u32(&port, channel, 0x10);
            port_set32(&port, channel, 0x14, value);
            port_set8(&port, channel, 1, port_u8(&port, channel, 1) | 2);
        }
    }
    else if (value >= 0xa0 && value <= 0xaf)
    {
        if (first && amount != 0)
        {
            value = amount << 2;
            port_set32(&port, channel, 0x48, value);
        }
    }
    else if (value >= 0xb0 && value <= 0xbf)
    {
        if (!first)
        {
            value = port_call_with(&port, 0x40d090, channel, channel, entry->ebx, entry->ecx,
                                   entry->esi, entry->edi, entry->ebp);
        }
        else if (amount != 0)
        {
            value = amount;
            port_set32(&port, channel, 0x44, value);
        }
    }
    else if (value >= 0xc0 && value <= 0xcf)
    {
        if (first)
        {
            value = amount << 4;
            port_set32(&port, channel, 0x1c, value);
            port_set8(&port, channel, 1, port_u8(&port, channel, 1) | 4);
        }
    }
    else if (value >= 0xd0 && value <= 0xef)
    {
        if (!first)
        {
            level = (int32_t)port_u32(&port, channel, 0x1c);
            if (value < 0xe0)
            {
                level -= (int32_t)amount;
                port_set32(&port, channel, 0x1c, (uint32_t)level);
                if (level < 0)
                {
                    port_set32(&port, channel, 0x1c, 0);
                }
            }
            else
            {
                level += (int32_t)amount;
                port_set32(&port, channel, 0x1c, (uint32_t)level);
                if (level > 0xff)
                {
                    port_set32(&port, channel, 0x1c, 0xff);
                }
            }
            port_set8(&port, channel, 1, port_u8(&port, channel, 1) | 4);
            value = amount;
        }
    }
    else if (value >= 0xf0)
    {
        if (!first)
        {
            value = port_call_with(&port, 0x40cff0, channel, channel, entry->ebx, entry->ecx,
                                   entry->esi, entry->edi, entry->ebp);
        }
    }
    return port_return(&port, value, entry->edx);
}
