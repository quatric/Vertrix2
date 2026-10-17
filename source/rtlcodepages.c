#include "rtlcodepages.h"

/* The runtime's _setmbcp: picks the multibyte code page and marks its lead bytes. */

enum
{
    /* The routine's frame under its return slot: the CPINFO GetCPInfo fills. */
    BELOW = 0x28,
    CPINFO = 0x24,
    CPINFO_LEAD_BYTES = 6,

    CP_ANSI = 0xffffffffu,
    CP_OEM = 0xfffffffeu,
    CP_SBCS = 0xfffffffdu,
    CP_SHIFT_JIS = 0xfffffffcu,
    SHIFT_JIS = 932,

    /* The lead byte table, indexed by byte + 1, and the code page state. */
    LEAD_BYTES = 0x5c8960,
    LEAD_BYTES_SIZE = 0x101,
    MULTIBYTE = 0x5c8950,
    CODE_PAGE = 0x50a820,

    GET_ACP = 0x4f1b7c,
    GET_OEMCP = 0x4f1bd0,
    GET_CPINFO = 0x4f1b80,
    MEMSET = 0x4eb5c0
};

static void clear_lead_bytes(Port *port)
{
    port_call(port, MEMSET, LEAD_BYTES, 0, LEAD_BYTES_SIZE, 0);
}

/* Marks the lead bytes from + 1 to to + 1 (the table is indexed by byte + 1). */
static void mark_lead_bytes(Port *port, int32_t from, int32_t to)
{
    for (int32_t byte = from; byte <= to && !port->env.failed; byte++)
    {
        port_set8(port, LEAD_BYTES, byte + 1, 1);
    }
}

/* Original 0x4e6f60 (eax = the code page: -1 ANSI, -2 OEM, -3 single byte, -4 Shift JIS, or a
 * number, 0 meaning 1): returns 0, or 1 when GetCPInfo fails. The caller's edx is kept. */
uint32_t vertrix_port_rtl_set_code_page_4e6f60(PORT_SIGNATURE)
{
    uint8_t stack[BELOW + 8];
    Port port;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    const uint32_t info = entry->esp - 4 - CPINFO;
    uint32_t code_page = entry->eax;

    switch (code_page)
    {
        case CP_ANSI:
            code_page = port_call(&port, GET_ACP, 0, 0, 0, 0);
            break;
        case CP_OEM:
            code_page = port_call(&port, GET_OEMCP, 0, 0, 0, 0);
            break;
        case CP_SBCS:
            clear_lead_bytes(&port);
            port_set32(&port, MULTIBYTE, 0, 0);
            port_set32(&port, CODE_PAGE, 0, 0);
            return port_return(&port, 0, entry->edx);
        case CP_SHIFT_JIS:
            clear_lead_bytes(&port);
            mark_lead_bytes(&port, 0x81, 0x9f);
            mark_lead_bytes(&port, 0xe0, 0xfc);
            port_set32(&port, MULTIBYTE, 0, 1);
            port_set32(&port, CODE_PAGE, 0, SHIFT_JIS);
            return port_return(&port, 0, entry->edx);
        default:
            break;
    }
    if (code_page == 0)
    {
        code_page = 1;
    }
    const uint32_t arguments[2] = {code_page, info};
    if (port_call_stack(&port, GET_CPINFO, 0, 0, 0, 0, arguments, 2) == 0)
    {
        return port_return(&port, 1, entry->edx);
    }
    clear_lead_bytes(&port);
    port_set32(&port, MULTIBYTE, 0, 0);
    const uint32_t lead = info + CPINFO_LEAD_BYTES;
    if (port_u8(&port, lead, 0) != 0)
    {
        port_set32(&port, MULTIBYTE, 0, 1);
    }
    /* The lead byte ranges, pairs ending with two zeros. */
    for (uint32_t pair = 0;
         (port_u8(&port, lead, pair) != 0 || port_u8(&port, lead, pair + 1) != 0) &&
         !port.env.failed;
         pair += 2)
    {
        mark_lead_bytes(&port, (int32_t)port_u8(&port, lead, pair),
                        (int32_t)port_u8(&port, lead, pair + 1));
    }
    port_set32(&port, CODE_PAGE, 0,
               code_page == 1 ? port_call(&port, GET_OEMCP, 0, 0, 0, 0) : code_page);
    return port_return(&port, 0, entry->edx);
}
