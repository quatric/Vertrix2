#include "rtlformatscans.h"

/* The runtime's scanf core: walks the format, skipping white space, matching literal characters
 * and running each conversion against the input. */

enum
{
    /* The routine's frame under its return slot: the format pointer and the argument list, which
     * the conversions advance by address. */
    BELOW = 0x18,
    FORMAT = 0x14,
    ARGUMENTS = 0x10,

    /* The input state: its flags (1 the conversion assigns, 2 end of input, 0x20 wide). */
    STATE_FLAGS = 0x10,
    FLAG_ASSIGN = 1,
    FLAG_END = 2,
    FLAG_WIDE = 0x20,

    /* The character class table, indexed by character + 1; 2 marks white space. */
    CHARACTER_CLASSES = 0x507d58,
    CLASS_SPACE = 2,

    SKIP_SPACE = 0x4e44c8,
    GET = 0x4e4100,
    UNGET = 0x4e4108,
    FIELD_WIDTH = 0x4e43c4,
    SCAN_INTEGER = 0x4e4bb0,
    SCAN_FLOAT = 0x4e48d8,
    SCAN_STRING = 0x4e45f0,
    SCAN_SET = 0x4e47ec,
    SCAN_CHARACTERS = 0x4e4508,
    STORE_COUNT = 0x4e4748
};

static void set_flag(Port *port, uint32_t state, uint32_t flag)
{
    port_set8(port, state, STATE_FLAGS, port_u8(port, state, STATE_FLAGS) | flag);
}

static int at_end(Port *port, uint32_t state)
{
    return (port_u8(port, state, STATE_FLAGS) & FLAG_END) != 0;
}

/* Reads the next input character and checks it against `expected`: 1 on a match; otherwise puts
 * it back unless the input ended, and returns 0. */
static int match(Port *port, uint32_t state, uint32_t expected, uint32_t ecx)
{
    const uint32_t got = port_call(port, GET, state, 0, expected, ecx);
    if (got == expected)
    {
        return 1;
    }
    if (!at_end(port, state))
    {
        port_call(port, UNGET, got, state, 0, ecx);
    }
    return 0;
}

/* A conversion that reads the input state in esi as well as eax. */
static uint32_t convert(Port *port, uint32_t target, uint32_t state, uint32_t arguments,
                        uint32_t ebx, uint32_t ecx)
{
    return port_call_with(port, target, state, arguments, ebx, ecx, state, 0, 0);
}

/* Original 0x4e4110 (eax = the input state, edx = the format, ebx = where the argument list is,
 * ecx as the callees get it): returns the number of fields assigned, or -1 when the input ended
 * before any. ecx is handed on as the original leaves it: the caller's, until an integer
 * conversion sets it to its signed flag. */
uint32_t vertrix_port_rtl_format_scan_4e4110(PORT_SIGNATURE)
{
    uint8_t stack[BELOW + 8];
    Port port;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    const uint32_t frame = entry->esp - 4;
    const uint32_t format = frame - FORMAT;
    const uint32_t arguments = frame - ARGUMENTS;
    const uint32_t state = entry->eax;
    uint32_t ecx = entry->ecx;
    uint32_t count = 0;
    uint32_t assigned = 0;

    port_set32(&port, format, 0, entry->edx);
    port_set32(&port, arguments, 0, port_u32(&port, entry->ebx, 0));
    port_set8(&port, state, STATE_FLAGS, port_u8(&port, state, STATE_FLAGS) & ~FLAG_END);
    for (;;)
    {
        const uint32_t at = port_u32(&port, format, 0);
        port_set32(&port, format, 0, at + 1);
        const uint32_t c = port_u8(&port, at, 0);
        if (c == 0 || port.env.failed)
        {
            break;
        }
        if ((port_u8(&port, CHARACTER_CLASSES, (c + 1) & 0xff) & CLASS_SPACE) != 0)
        {
            count += port_call(&port, SKIP_SPACE, state, 0, 0, ecx);
        }
        else if (c != '%')
        {
            if (!match(&port, state, c, ecx))
            {
                break;
            }
            count++;
        }
        else
        {
            uint32_t spec = port_call(&port, FIELD_WIDTH, port_u32(&port, format, 0), state, 0, 0);
            const uint32_t conversion = port_u8(&port, spec, 0);
            if (conversion != 0)
            {
                spec++;
            }
            port_set32(&port, format, 0, spec);
            int32_t scanned = 0;
            int converted = 1;
            switch (conversion)
            {
                case 'd':
                    ecx = 1;
                    scanned = (int32_t)port_call(&port, SCAN_INTEGER, state, arguments, 10, ecx);
                    break;
                case 'i':
                    ecx = 1;
                    scanned = (int32_t)port_call(&port, SCAN_INTEGER, state, arguments, 0, ecx);
                    break;
                case 'o':
                    ecx = 1;
                    scanned = (int32_t)port_call(&port, SCAN_INTEGER, state, arguments, 8, ecx);
                    break;
                case 'u':
                    ecx = 0;
                    scanned = (int32_t)port_call(&port, SCAN_INTEGER, state, arguments, 10, ecx);
                    break;
                case 'p':
                case 'x':
                case 'X':
                    ecx = 1;
                    scanned = (int32_t)port_call(&port, SCAN_INTEGER, state, arguments, 16, ecx);
                    break;
                case 'e':
                case 'f':
                case 'g':
                case 'E':
                case 'G':
                    scanned =
                        (int32_t)port_call(&port, SCAN_FLOAT, state, arguments, conversion, 0);
                    break;
                case 'S':
                    set_flag(&port, state, FLAG_WIDE);
                    /* Fall through. */
                case 's':
                    scanned = (int32_t)convert(&port, SCAN_STRING, state, arguments, conversion, 0);
                    break;
                case '[':
                    scanned = (int32_t)convert(&port, SCAN_SET, state, arguments, format, ecx);
                    break;
                case 'C':
                    set_flag(&port, state, FLAG_WIDE);
                    /* Fall through. */
                case 'c':
                    scanned =
                        (int32_t)convert(&port, SCAN_CHARACTERS, state, arguments, conversion, 0);
                    break;
                case 'n':
                    port_call(&port, STORE_COUNT, state, arguments, count, 0);
                    converted = 0;
                    break;
                case '%':
                    if (!match(&port, state, '%', ecx))
                    {
                        goto done;
                    }
                    count++;
                    converted = 0;
                    break;
                default:
                    converted = 0;
                    break;
            }
            if (converted)
            {
                if (scanned <= 0)
                {
                    break;
                }
                count += (uint32_t)scanned;
                if ((port_u8(&port, state, STATE_FLAGS) & FLAG_ASSIGN) != 0)
                {
                    assigned++;
                }
            }
        }
        if (at_end(&port, state))
        {
            /* A %n right after the input ends still stores the count. */
            const uint32_t rest = port_u32(&port, format, 0);
            if (port_u8(&port, rest, 0) == '%')
            {
                port_set32(&port, format, 0, rest + 1);
                const uint32_t spec = port_call(&port, FIELD_WIDTH, rest + 1, state, 0, 0);
                port_set32(&port, format, 0, spec);
                if (port_u8(&port, spec, 0) == 'n')
                {
                    port_call(&port, STORE_COUNT, state, arguments, count, 0);
                }
            }
            break;
        }
    }
done:
    if (assigned == 0 && at_end(&port, state))
    {
        return port_return(&port, 0xffffffffu, 0);
    }
    return port_return(&port, assigned, 0);
}
