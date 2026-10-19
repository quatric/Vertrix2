#include "rtlwidetexts.h"

enum
{
    BELOW = 0x20,
    /* The multibyte character, under the saved esi, edi, es and ebp. */
    CHARACTER = 0x14,
    /* The printf state: the characters still allowed. */
    LEFT = 0x28,

    WIDE_TO_MULTIBYTE = 0x4e62e0
};

/* Original 0x4dfac0 (eax = the wide string, edx = its segment, ebx = the printf state, ecx = the
 * output procedure): printf's output of a wide string. While the state allows characters (+0x28,
 * signed), each wide character is converted (wctomb, 0x4e62e0, into a local) and its bytes go to
 * the output procedure (eax = the state, edx = the byte, ecx = the bytes still to go after it),
 * each counting one down. One that cannot be converted (-1) is skipped; one longer than what is
 * left sets it to 0 and ends. The string has no terminator check: only the count stops it. */
uint32_t vertrix_port_rtl_wide_text_4dfac0(PORT_SIGNATURE)
{
    Port port;
    uint8_t stack[BELOW + 8];
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    const uint32_t state = entry->ebx;
    const uint32_t output = entry->ecx;
    const uint32_t character = entry->esp - CHARACTER;
    uint32_t text = entry->eax;
    while ((int32_t)port_u32(&port, state, LEFT) > 0 && !port.env.failed)
    {
        const uint32_t wide = port_u16(&port, text, 0);
        text += 2;
        const uint32_t length = port_call(&port, WIDE_TO_MULTIBYTE, character, wide, 0, 0);
        if (length == 0xffffffffu)
        {
            continue;
        }
        if ((int32_t)length > (int32_t)port_u32(&port, state, LEFT))
        {
            port_set32(&port, state, LEFT, 0);
            break;
        }
        for (uint32_t i = 0; i < length && !port.env.failed; i++)
        {
            port_call(&port, output, state, port_u8(&port, character, i), state, length - 1 - i);
            port_set32(&port, state, LEFT, port_u32(&port, state, LEFT) - 1);
        }
    }
    return port_return(&port, 0, vertrix_lift_edx);
}
