#include "port_rtlformatwidths.h"

/* Part of the runtime's printf: after the flags, reads a field's width or precision (digits or *)
 * and its size prefix (N, F, h, l, w, L, I64). */

enum
{
    SPEC_WIDTH = 0xc,
    SPEC_FLAGS = 0x10,
    /* Flag bits: 1 the number came from the text (cleared for *), 4 F, 8 N, 0x10 h, 0x20 l or w,
     * 0x40 L or I64. Bit 2 is kept from before, the rest cleared. */
    FLAG_GIVEN = 1,
    FLAG_KEPT = 3,
    FLAG_FAR = 4,
    FLAG_NEAR = 8,
    FLAG_SHORT = 0x10,
    FLAG_LONG = 0x20,
    FLAG_INT64 = 0x40,

    /* The runtime's character class table, indexed by character + 1; 0x20 marks a digit. */
    CHARACTER_CLASSES = 0x507d58,
    CLASS_DIGIT = 0x20
};

static int is_digit(Port *port, uint32_t c)
{
    return (port_u8(port, CHARACTER_CLASSES, (c + 1) & 0xff) & CLASS_DIGIT) != 0;
}

static void set_flag(Port *port, uint32_t spec, uint32_t flag)
{
    port_set8(port, spec, SPEC_FLAGS, port_u8(port, spec, SPEC_FLAGS) | flag);
}

/* Original 0x4e43c4 (eax = the text, edx = the field): sets the width to -1, then to the digits'
 * value if there are any, and the flags; returns the text after what it read. */
uint32_t vertrix_port_rtl_format_width_4e43c4(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    uint32_t text = entry->eax;
    const uint32_t spec = entry->edx;

    port_set8(&port, spec, SPEC_FLAGS, (port_u8(&port, spec, SPEC_FLAGS) | FLAG_GIVEN) & FLAG_KEPT);
    port_set32(&port, spec, SPEC_WIDTH, 0xffffffffu);
    if (port_u8(&port, text, 0) == '*')
    {
        port_set8(&port, spec, SPEC_FLAGS, port_u8(&port, spec, SPEC_FLAGS) & ~FLAG_GIVEN);
        text++;
    }
    uint32_t c = port_u8(&port, text, 0);
    if (is_digit(&port, c))
    {
        uint32_t width = 0;
        do
        {
            width = width * 10 + c - '0';
            c = port_u8(&port, text, 1);
            text++;
        } while (is_digit(&port, c) && !port.env.failed);
        port_set32(&port, spec, SPEC_WIDTH, width);
    }

    c = port_u8(&port, text, 0);
    if (c == 'N')
    {
        set_flag(&port, spec, FLAG_NEAR);
        text++;
    }
    else if (c == 'F')
    {
        set_flag(&port, spec, FLAG_FAR);
        text++;
    }

    switch (port_u8(&port, text, 0))
    {
        case 'h':
            set_flag(&port, spec, FLAG_SHORT);
            text++;
            break;
        case 'l':
        case 'w':
            set_flag(&port, spec, FLAG_LONG);
            text++;
            break;
        case 'L':
            set_flag(&port, spec, FLAG_INT64);
            text++;
            break;
        case 'I':
            if (port_u8(&port, text, 1) == '6' && port_u8(&port, text, 2) == '4')
            {
                set_flag(&port, spec, FLAG_INT64);
                text += 3;
            }
            break;
        default:
            break;
    }
    return port_return(&port, text, 0);
}
