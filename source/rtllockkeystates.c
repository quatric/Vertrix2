#include "rtllockkeystates.h"

enum
{
    /* MFC's status bar indicators. */
    INDICATOR_CAPS = 0xe701,
    INDICATOR_NUM = 0xe702,
    INDICATOR_SCRL = 0xe703,
    INDICATOR_KANA = 0xe706,
    VK_CAPITAL = 0x14,
    VK_KANA = 0x15,
    VK_NUMLOCK = 0x90,
    VK_SCROLL = 0x91,
    TOGGLED = 1,
    DOWN = 0x8000,
    /* Kana reads the key's down bit, not its toggle, when this is set. */
    KANA_BY_DOWN = 0x5c79c8,
    GET_KEY_STATE = 0x4f1998,

    /* The CCmdUI: its command id, the flag that passes the update on, and its method table (the
     * first method enables or disables the item). */
    COMMAND_ID = 0,
    CONTINUE_ROUTING = 0x18,
    METHODS = 0x24,
    ENABLE = 0
};

/* Original 0x4d5bf8 (eax = frame, edx = CCmdUI): MFC's CFrameWnd::OnUpdateKeyIndicator: the Caps
 * Lock, Num Lock, Scroll Lock and Kana indicators are enabled by their key's toggle state
 * (GetKeyState & 1; Kana's down bit 0x8000 when 0x5c79c8 is set); any other command passes the
 * update on (+0x18 = 1) and returns the command id less 0xe701, with edx the CCmdUI. Otherwise
 * returns what Enable returns, edx too (its callers read it). */
uint32_t vertrix_port_lock_key_state_query_4d5bf8(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t cmd_ui = entry->edx;
    const uint32_t id = port_u32(&port, cmd_ui, COMMAND_ID);
    uint32_t key;
    uint32_t bit = TOGGLED;
    switch (id)
    {
        case INDICATOR_CAPS:
            key = VK_CAPITAL;
            break;
        case INDICATOR_NUM:
            key = VK_NUMLOCK;
            break;
        case INDICATOR_SCRL:
            key = VK_SCROLL;
            break;
        case INDICATOR_KANA:
            key = VK_KANA;
            if (port_u32(&port, KANA_BY_DOWN, 0) != 0)
            {
                bit = DOWN;
            }
            break;
        default:
            port_set32(&port, cmd_ui, CONTINUE_ROUTING, 1);
            return port_return(&port, id - INDICATOR_CAPS, cmd_ui);
    }
    const uint32_t state = port_call_stack(&port, GET_KEY_STATE, 0, 0, 0, 0, &key, 1);
    const uint32_t enable = (uint32_t)(int32_t)(int16_t)state & bit;
    /* A virtual call: the original also leaves the CCmdUI in ebx and the caller's ecx. */
    const uint32_t method = port_u32(&port, port_u32(&port, cmd_ui, METHODS), ENABLE);
    const uint32_t result = port_call(&port, method, cmd_ui, enable, cmd_ui, entry->ecx);
    return port_return(&port, result, vertrix_lift_edx);
}
