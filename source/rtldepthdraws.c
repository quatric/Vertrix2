#include "rtldepthdraws.h"

enum
{
    /* The list: the items (+4) and their count (+8, a word). An item's depth is the word at +0x16,
     * its method table at +0x158, and its draw method at slot +8. */
    LIST_ITEMS = 4,
    LIST_COUNT = 8,
    ITEM_DEPTH = 0x16,
    ITEM_METHODS = 0x158,
    METHOD_DRAW = 8,

    /* A depth of 0x7d00 marks an item drawn (and the minimum found when none is left). */
    DRAWN = 0x7d00,

    ITEMS = 0x5bc01c,
    DEPTHS = 0x5bd01c,
    MINIMUM = 0x5bd81c,
    INDEX = 0x5bd820,
    COUNT = 0x5bd822,
    LAST = 0x5bd824
};

static uint32_t count_of(Port *port)
{
    return port_u16(port, COUNT, 0);
}

/* Original 0x4b6240 (eax = the list, edx = handed to each draw): copies the items and their depths
 * into 0x5bc01c and 0x5bd01c (the count into 0x5bd822, the last item into 0x5bd824), then draws
 * them from the least depth up (signed words): each round finds the least depth left and draws
 * every item at that depth in list order (method +8, with the item in eax, edx in edx and ecx, the
 * index in ebx and the table in esi, as the original leaves them), marking it 0x7d00. The minimum
 * and the index are kept in 0x5bd81c and 0x5bd820, and read back after each draw; the count is read
 * again each time. eax is what the original leaves in it: the last index the rounds looked at
 * (doubled when the search for the least depth was last), or the count when there were no items;
 * no caller reads edx. */
uint32_t vertrix_port_depth_ordered_draw_4b6240(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t list = entry->eax;
    const uint32_t handed = entry->edx;
    uint32_t eax = port_u32(&port, list, LIST_COUNT);
    port_set16(&port, COUNT, 0, eax);
    if ((uint16_t)eax != 0)
    {
        uint32_t i = 0;
        do
        {
            const uint32_t item = port_u32(&port, port_u32(&port, list, LIST_ITEMS), i * 4);
            port_set32(&port, ITEMS + i * 4, 0, item);
            port_set32(&port, LAST, 0, item);
            port_set16(&port, DEPTHS + i * 2, 0, port_u16(&port, item, ITEM_DEPTH));
            eax = item;
            i = (i + 1) & 0xffff;
        } while (i < count_of(&port) && !port.env.failed);
    }
    uint32_t index = 0;
    while (!port.env.failed)
    {
        uint16_t minimum = DRAWN;
        index = 0;
        if (count_of(&port) != 0)
        {
            do
            {
                eax = index * 2;
                const uint16_t depth = port_u16(&port, DEPTHS + index * 2, 0);
                if ((int16_t)depth < (int16_t)minimum)
                {
                    minimum = depth;
                }
                index = (index + 1) & 0xffff;
            } while (index < count_of(&port) && !port.env.failed);
        }
        if (minimum == DRAWN)
        {
            port_set16(&port, MINIMUM, 0, minimum);
            port_set16(&port, INDEX, 0, index);
            break;
        }
        index = 0;
        if (count_of(&port) == 0)
        {
            continue;
        }
        do
        {
            eax = index;
            const uint16_t depth = port_u16(&port, DEPTHS + index * 2, 0);
            port_set16(&port, MINIMUM, 0, minimum);
            if (depth == minimum)
            {
                const uint32_t item = port_u32(&port, ITEMS + index * 4, 0);
                const uint32_t methods = port_u32(&port, item, ITEM_METHODS);
                port_set16(&port, INDEX, 0, index);
                port_call_with(&port, port_u32(&port, methods, METHOD_DRAW), item, handed, index,
                               handed, methods, minimum, entry->ebp);
                index = port_u16(&port, INDEX, 0);
                eax = index;
                port_set16(&port, DEPTHS + index * 2, 0, DRAWN);
            }
            minimum = port_u16(&port, MINIMUM, 0);
            index = (index + 1) & 0xffff;
        } while (index < count_of(&port) && !port.env.failed);
    }
    return port_return(&port, eax, 0);
}
