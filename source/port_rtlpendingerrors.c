#include "port_rtlpendingerrors.h"

/* The runtime's console getch: reads key events from the console input, handing out a key's
 * character once per repeat, and an extended key as 0 followed by its scan code. */

enum
{
    /* The routine's frame under its return slot: the input record and the count read. */
    BELOW = 0x30,
    RECORD = 0x2c,
    READ_COUNT = 0x18,

    /* A KEY_EVENT_RECORD inside the INPUT_RECORD. */
    KEY_REPEAT_COUNT = 8,
    KEY_SCAN_CODE = 0xc,
    KEY_CHARACTER = 0xe,
    KEY_CONTROL_STATE_HIGH = 0x11,
    /* ENHANCED_KEY (0x100) in the control state's second byte. */
    ENHANCED_KEY = 1,

    /* 0 nothing pending, 1 the character repeats, 2 a scan code follows. */
    PENDING = 0x50ba74,
    PENDING_SCAN_CODE = 0x5c8af0,
    PENDING_CHARACTER = 0x5c8af4,
    PENDING_REPEATS = 0x5c8af8,
    NOTHING = 0,
    REPEATING = 1,
    SCAN_CODE_NEXT = 2,

    READ_CONSOLE_INPUT = 0x4f1c74,
    IS_KEY_PRESS = 0x4e8950
};

/* Original 0x4ed880 (eax = the console input handle): returns the next character, 0 for an
 * extended key (its scan code comes next), or -1 when the console cannot be read. */
uint32_t vertrix_port_rtl_console_getch_4ed880(PORT_SIGNATURE)
{
    uint8_t stack[BELOW + 8];
    Port port;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    const uint32_t record = entry->esp - 4 - RECORD;
    const uint32_t read_count = entry->esp - 4 - READ_COUNT;
    const uint32_t handle = entry->eax;
    uint32_t repeats = port_u32(&port, PENDING_REPEATS, 0);
    uint32_t character = port_u32(&port, PENDING_CHARACTER, 0);
    uint32_t result;

    switch (port_u32(&port, PENDING, 0))
    {
        case REPEATING:
            repeats--;
            if (character == 0)
            {
                port_set32(&port, PENDING, 0, SCAN_CODE_NEXT);
            }
            else if (repeats == 0)
            {
                port_set32(&port, PENDING, 0, NOTHING);
            }
            result = character;
            break;
        case SCAN_CODE_NEXT:
            port_set32(&port, PENDING, 0, repeats != 0 ? REPEATING : NOTHING);
            result = port_u32(&port, PENDING_SCAN_CODE, 0);
            break;
        default:
            port_set32(&port, PENDING_REPEATS, 0, repeats);
            port_set32(&port, PENDING_CHARACTER, 0, character);
            for (;;)
            {
                const uint32_t arguments[4] = {handle, record, 1, read_count};
                if (port_call_stack(&port, READ_CONSOLE_INPUT, 0, 0, 0, 0, arguments, 4) == 0 ||
                    port.env.failed)
                {
                    result = 0xffffffffu;
                    character = port_u32(&port, PENDING_CHARACTER, 0);
                    repeats = port_u32(&port, PENDING_REPEATS, 0);
                    break;
                }
                if (port_call(&port, IS_KEY_PRESS, record, 0, 0, 0) == 0)
                {
                    continue;
                }
                repeats = port_u16(&port, record, KEY_REPEAT_COUNT) - 1;
                character = port_u8(&port, record, KEY_CHARACTER);
                if ((port_u8(&port, record, KEY_CONTROL_STATE_HIGH) & ENHANCED_KEY) != 0 ||
                    character == 0)
                {
                    character = 0;
                    port_set32(&port, PENDING, 0, SCAN_CODE_NEXT);
                    port_set32(&port, PENDING_SCAN_CODE, 0, port_u16(&port, record, KEY_SCAN_CODE));
                }
                else if (repeats != 0)
                {
                    port_set32(&port, PENDING, 0, REPEATING);
                }
                result = character;
                break;
            }
            break;
    }
    port_set32(&port, PENDING_CHARACTER, 0, character);
    port_set32(&port, PENDING_REPEATS, 0, repeats);
    return port_return(&port, result, 0);
}
