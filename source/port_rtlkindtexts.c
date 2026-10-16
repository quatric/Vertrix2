#include "port_rtlkindtexts.h"

/* The texts that name an error's kind. */

/* Original 0x488d80 (guarded 0x5170bc): the string eax set to 0x510737 (0x4ca280), then by the
 * kind +8 of the error edx (0..14) to its text from 0x510755..0x51097f (0x4ca370); another kind
 * keeps the first. eax the string. */
uint32_t vertrix_port_error_kind_text_488d80(PORT_SIGNATURE)
{
    static const uint32_t texts[15] = {0x510755, 0x510768, 0x510787, 0x5107a6, 0x5107ca,
                                       0x5107fb, 0x51081b, 0x51084f, 0x510880, 0x5108a5,
                                       0x5108d8, 0x5108f4, 0x51092d, 0x51096d, 0x51097f};
    enum
    {
        BELOW = 0x28
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t record = ebp - 0x24;
    uint32_t text = entry->eax;
    uint32_t error = entry->edx;
    uint32_t kind;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->esi);
    port_set32(&port, ebp, -0x10u, entry->edi);
    port_set32(&port, record, 0, port.env.chain);
    port.env.chain = record;
    port_set32(&port, ebp, -0x20u, 0x4ec1ec);
    port_set32(&port, ebp, -0x1cu, 0x5170bc);
    port_set32(&port, ebp, -0x18u, 0);
    port_call_with(&port, 0x4ca280, text, 0x510737, error, text, 0x5170bc, 0, ebp);
    kind = port_u32(&port, error, 8);
    if (kind < 15)
    {
        port_call_with(&port, 0x4ca370, text, texts[kind], error, text, 0x5170bc, 0, ebp);
    }
    port.env.chain = port_u32(&port, record, 0);
    return port_return(&port, text, vertrix_lift_edx);
}
