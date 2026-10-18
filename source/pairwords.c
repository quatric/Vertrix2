#include "pairwords.h"

/* The two players' key words: their acknowledgement and their snapshot. */

/* Original 0x473630: unless 0x532a84 is set, the keys of both players (0x540f8c, then 0x540f90;
 * the words +0x160..+0x166) are acknowledged on the input 0x54d640 (0x476320); the input takes
 * the key 0x5bd834 (0x476440) and is reset (0x476010 with 0). Then, with 0x532a84 still clear,
 * each of those keys is paired with the word 8 after it (0x4735e0). ebx, ecx and edx kept. */
uint32_t vertrix_port_pair_words_473630(PORT_SIGNATURE)
{
    Port port;
    uint32_t first;
    uint32_t second;
    uint32_t owner;
    uint32_t eax;
    unsigned side;
    unsigned key;
    port_open(&port, calls, services, globals, entry);
    first = port_u32(&port, 0, 0x540f8c);
    second = port_u32(&port, 0, 0x540f90);
    if (port_u32(&port, 0, 0x532a84) == 0)
    {
        for (side = 0; side < 2; side++)
        {
            owner = side == 0 ? first : second;
            for (key = 0; key < 4; key++)
            {
                port_forward(&port, entry, 0x476320, 0x54d640,
                             port_u16(&port, owner, 0x160 + key * 2), second, first);
            }
        }
    }
    port_forward(&port, entry, 0x476440, 0x54d640, port_u32(&port, 0, 0x5bd834), second, first);
    eax = port_forward(&port, entry, 0x476010, 0x54d640, 0, second, first);
    if (port_u32(&port, 0, 0x532a84) != 0)
    {
        return port_return(&port, eax, entry->edx);
    }
    for (side = 0; side < 2; side++)
    {
        owner = side == 0 ? first : second;
        for (key = 0; key < 4; key++)
        {
            eax = port_forward(&port, entry, 0x4735e0, port_u16(&port, owner, 0x160 + key * 2),
                               port_u16(&port, owner, 0x168 + key * 2), second, first);
        }
    }
    return port_return(&port, eax, entry->edx);
}

/* The keys +0x164, +0x166, +0x160 and +0x162 of `owner` read down (0x476480) into the four bytes
 * at `bytes`, then the four acknowledged (0x476320 of +0x160..+0x166). */
static uint32_t pair_snapshot(Port *port, const LiftEntry *entry, uint32_t owner, uint32_t bytes)
{
    static const uint32_t order[4] = {0x164, 0x166, 0x160, 0x162};
    uint32_t eax = 0;
    unsigned key;
    for (key = 0; key < 4; key++)
    {
        port_set8(port, 0, bytes + key,
                  port_forward(port, entry, 0x476480, 0x54d640, port_u16(port, owner, order[key]),
                               entry->ebx, owner));
    }
    for (key = 0; key < 4; key++)
    {
        eax = port_forward(port, entry, 0x476320, 0x54d640, port_u16(port, owner, 0x160 + key * 2),
                           entry->ebx, owner);
    }
    return eax;
}

/* Original 0x473af0: the player (0x540f90 when 0x532a7c is 1, else 0x540f8c) has its keys read
 * into 0x5bb594..0x5bb597 and acknowledged, the input 0x54d640 takes the key 0 (0x476440) and is
 * reset (0x476010 with 0), and the keys are read again into 0x5bb598..0x5bb59b and acknowledged.
 * ecx and edx kept. */
uint32_t vertrix_port_pair_scan_473af0(PORT_SIGNATURE)
{
    Port port;
    uint32_t owner;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    owner = port_u32(&port, 0, port_u32(&port, 0, 0x532a7c) == 1 ? 0x540f90 : 0x540f8c);
    pair_snapshot(&port, entry, owner, 0x5bb594);
    port_forward(&port, entry, 0x476440, 0x54d640, 0, entry->ebx, owner);
    port_forward(&port, entry, 0x476010, 0x54d640, 0, entry->ebx, owner);
    eax = pair_snapshot(&port, entry, owner, 0x5bb598);
    return port_return(&port, eax, entry->edx);
}
