#include "rtlancestors.h"

/* MFC's _AfxIsDescendant: whether a window is the parent's descendant through its parents and
 * owners. */

enum
{
    ARGUMENT_PARENT = 4,
    ARGUMENT_CHILD = 8,
    GET_PARENT_OWNER = 0x4d1890
};

/* Original 0x4d4390 (stdcall: parent, child): 1 when a step of _AfxGetParentOwner (0x4d1890) from
 * the child reaches the parent (or they are the same window), else 0. 0x4d1890 gets the eax the
 * original leaves (the caller's, then the last result) and the caller's esi, edi and ebp, which
 * its exception machinery reads. */
uint32_t vertrix_port_rtl_ancestor_search_4d4390(PORT_SIGNATURE)
{
    uint8_t stack[8 + 4 * 2];
    Port port;
    port_open_arguments(&port, stack, calls, services, globals, entry, 0, 2);
    const uint32_t parent = port_u32(&port, entry->esp, ARGUMENT_PARENT);
    uint32_t window = port_u32(&port, entry->esp, ARGUMENT_CHILD);
    if (parent == window)
    {
        return port_return(&port, 1, 0);
    }
    uint32_t eax = entry->eax;
    while (!port.env.failed)
    {
        window = port_forward_stack(&port, entry, GET_PARENT_OWNER, eax, 0, 0, 0, entry->esi,
                                    &window, 1);
        eax = window;
        if (window == 0)
        {
            return port_return(&port, 0, 0);
        }
        if (window == parent)
        {
            return port_return(&port, 1, 0);
        }
    }
    return port_return(&port, 0, 0);
}
