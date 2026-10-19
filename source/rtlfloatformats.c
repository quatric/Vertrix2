#include "rtlfloatformats.h"

enum
{
    /* The frame under the saved ebp, ecx, esi and edi: the conversion's parameters at its foot,
     * the long double above them and the double from the arguments above that. */
    BELOW = 0x50,
    PARAMETERS = 0x50,
    EXTENDED = 0x24,
    VALUE = 0x18,

    /* The parameters 0x4eccb9 takes. */
    PRECISION = 0,
    TRIM = 4,
    MODE = 8,
    LETTER = 0xc,
    CLEAR = 0x10,
    SIGN = 0x14,
    RESULTS = 0x1c,

    /* The printf state. */
    STATE_PRECISION = 8,
    STATE_LETTER = 0x15,
    STATE_FLAGS = 0x1e,
    STATE_LENGTH = 0x20,
    STATE_RESULTS = 0x28,

    FLAG_ALTERNATE = 1,
    FLAG_SPACE = 2,
    FLAG_PLUS = 4,
    MODE_ALTERNATE = 0x10,

    DATA_SELECTOR = 0x10,
    TO_EXTENDED = 0x4e53b4,
    CONVERT = 0x4eccb9
};

/* Original 0x4ec970 (eax = the text, edx = where the argument pointer is, ebx = the printf state):
 * printf's %e, %f and %g. The letter (+0x15) picks the conversion's mode: G (either case) 4 with
 * trimming and the letter two before (e or E), its precision 1 for 0; E 1 with trimming; anything
 * else 2. The # flag adds 0x10. The next double argument is taken (the pointer moved 8 on), made a
 * long double (0x4e53b4) and converted into the text after its first byte (0x4eccb9, at most 6
 * digits for a precision of -1), whose four results go to the state (+0x28). The first byte is
 * the sign: '-' for a negative value, else '+' or ' ' as the flags ask, counted in the state's
 * length (+0x20). Returns the text, edx the data selector. */
uint32_t vertrix_port_rtl_float_format_4ec970(PORT_SIGNATURE)
{
    Port port;
    uint8_t stack[BELOW + 8];
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    const uint32_t text = entry->eax;
    const uint32_t arguments = entry->edx;
    const uint32_t state = entry->ebx;
    const uint32_t parameters = entry->esp - PARAMETERS;
    const uint32_t extended = entry->esp - EXTENDED;
    const uint32_t value = entry->esp - VALUE;
    uint32_t letter = port_u8(&port, state, STATE_LETTER);
    uint32_t precision = port_u32(&port, state, STATE_PRECISION);
    uint32_t mode;
    uint32_t trim;
    switch (letter & 0x5f)
    {
        case 'G':
            if (precision == 0)
            {
                precision = 1;
            }
            mode = 4;
            trim = 1;
            letter -= 2;
            break;
        case 'E':
            mode = 1;
            trim = 1;
            break;
        default:
            mode = 2;
            trim = 0;
            break;
    }
    if (port_u8(&port, state, STATE_FLAGS) & FLAG_ALTERNATE)
    {
        mode |= MODE_ALTERNATE;
    }
    const uint32_t next = port_u32(&port, arguments, 0) + 8;
    port_set32(&port, arguments, 0, next);
    port_set32(&port, value, 0, port_u32(&port, next, -8u));
    port_set32(&port, value, 4, port_u32(&port, next, -4u));
    port_call(&port, TO_EXTENDED, value, extended, state, state);
    if (precision == 0xffffffffu)
    {
        precision = 6;
    }
    port_set32(&port, parameters, PRECISION, precision);
    port_set32(&port, parameters, TRIM, trim);
    port_set32(&port, parameters, MODE, mode);
    port_set32(&port, parameters, LETTER, letter);
    port_set32(&port, parameters, CLEAR, 0);
    port_call(&port, CONVERT, extended, parameters, text + 1, state);
    for (uint32_t i = 0; i < 16; i += 4)
    {
        port_set32(&port, state, STATE_RESULTS + i, port_u32(&port, parameters, RESULTS + i));
    }
    const uint32_t flags = port_u8(&port, state, STATE_FLAGS);
    uint32_t sign = 0;
    if ((int32_t)port_u32(&port, parameters, SIGN) < 0)
    {
        sign = '-';
    }
    else if (flags & FLAG_PLUS)
    {
        sign = '+';
    }
    else if (flags & FLAG_SPACE)
    {
        sign = ' ';
    }
    if (sign != 0)
    {
        const uint32_t length = port_u32(&port, state, STATE_LENGTH);
        port_set32(&port, state, STATE_LENGTH, length + 1);
        port_set8(&port, text, length, sign);
    }
    return port_return(&port, text, DATA_SELECTOR);
}
