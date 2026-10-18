#include "rtlsettingsaves.h"

/* Game settings saved. */

/* The text at `source` copied to `target` up to and including its end 0, two bytes a step; the
 * source place the copy stops at. */
static uint32_t copy_text(Port *port, uint32_t target, uint32_t source)
{
    uint32_t index = 0;
    for (;;)
    {
        uint32_t value = port_u8(port, source, index);
        port_set8(port, target, index, value);
        if (value == 0 || port->env.failed)
        {
            return source + index;
        }
        value = port_u8(port, source, index + 1);
        port_set8(port, target, index + 1, value);
        index += 2;
        if (value == 0)
        {
            return source + index;
        }
    }
}

/* Original 0x415860 (guarded 0x513a20): the settings saved: the file name 0x4fd310 with 0x50d3bc
 * made in the frame (0x45f540), a settings record given its defaults (0x4290c0) and its body
 * (0x429660) filled from the game: 0x532b4c and 0x532b54..0x532b64 at +0..+0x14, the keys
 * 0x532b6c..0x532b7c at +0x18..+0x28, 0x532b98..0x532bac at +0x2c..+0x40, 0x532b80/0x532b84 at
 * +0x44/+0x48, 0x532b88 at +0x4c, 0x532bb4/0x532bb8 at +0x50/+0x54, the five 0x533294 at +0x58,
 * the five texts 0x5332a8 at +0x6c on (4 apart), 0x532bd4..0x532be4 at +0x80..+0x90 and the texts
 * 0x532be8, 0x532bec, 0x532bf0 and 0x532bf4 at +0x94, +0xf8, +0x15c and +0x1c0; written to the
 * file (0x429460) and released (0x429350). eax the restored chain, edx kept. */
uint32_t vertrix_port_settings_save_415860(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x364
    };
    static const uint32_t longs[][2] = {{0x0, 0x532b4c},  {0x4, 0x532b54},  {0x8, 0x532b58},
                                        {0xc, 0x532b5c},  {0x10, 0x532b60}, {0x14, 0x532b64},
                                        {0x44, 0x532b80}, {0x48, 0x532b84}};
    static const uint32_t later[][2] = {{0x4c, 0x532b88}, {0x2c, 0x532b98}, {0x30, 0x532b9c},
                                        {0x34, 0x532ba0}, {0x38, 0x532ba4}, {0x3c, 0x532ba8},
                                        {0x40, 0x532bac}, {0x50, 0x532bb4}, {0x54, 0x532bb8}};
    static const uint32_t texts[4][2] = {
        {0x94, 0x532be8}, {0xf8, 0x532bec}, {0x15c, 0x532bf0}, {0x1c0, 0x532bf4}};
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t record = ebp - 0x2c;
    uint32_t settings = ebp - 0x35c;
    uint32_t file = ebp - 0x130;
    uint32_t body;
    uint32_t esi;
    uint32_t edi;
    uint32_t source;
    unsigned index;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    port_set32(&port, ebp, -0x14u, entry->edi);
    port_set32(&port, record, 0, port.env.chain);
    port.env.chain = record;
    port_set32(&port, ebp, -0x28u, 0x4ec1ec);
    port_set32(&port, ebp, -0x20u, 0);
    port_set32(&port, ebp, -0x24u, 0x513a20);
    port_call_with(&port, 0x45f540, file, 0x4fd310, 0x50d3bc, 0x513a20, entry->esi, entry->edi,
                   ebp);
    port_call_with(&port, 0x4290c0, settings, vertrix_lift_edx, 0x50d3bc, 0x513a20, 1, entry->edi,
                   ebp);
    port_set32(&port, ebp, -0x20u, 1);
    body = port_call_with(&port, 0x429660, settings, vertrix_lift_edx, 0x50d3bc, 0x513a20, 1,
                          entry->edi, ebp);
    port_set32(&port, ebp, -0x18u, body);
    for (index = 0; index < sizeof longs / sizeof longs[0]; index++)
    {
        port_set32(&port, body, longs[index][0], port_u32(&port, 0, longs[index][1]));
    }
    for (index = 0; index < 9; index++)
    {
        port_set16(&port, body, 0x18 + index * 2, port_u16(&port, 0, 0x532b6c + index * 2));
    }
    for (index = 0; index < sizeof later / sizeof later[0]; index++)
    {
        port_set32(&port, body, later[index][0], port_u32(&port, 0, later[index][1]));
    }
    for (index = 0; index < 5; index++)
    {
        port_set32(&port, body, 0x58 + index * 4, port_u32(&port, 0, 0x533294 + index * 4));
    }
    esi = 1;
    for (index = 0; index < 5 && !port.env.failed; index++)
    {
        edi = body + 0x6c + index * 4;
        port_set32(&port, ebp, -0x360u, edi);
        esi = copy_text(&port, edi, port_u32(&port, 0, 0x5332a8 + index * 4));
    }
    port_set32(&port, body, 0x80, port_u32(&port, 0, 0x532bd4));
    port_set32(&port, body, 0x84, port_u32(&port, 0, 0x532bd8));
    port_set32(&port, body, 0x88, port_u32(&port, 0, 0x532bdc));
    port_set32(&port, body, 0x8c, port_u32(&port, 0, 0x532be0));
    port_set32(&port, body, 0x90, port_u32(&port, 0, 0x532be4));
    edi = body;
    for (index = 0; index < 4 && !port.env.failed; index++)
    {
        edi = body + texts[index][0];
        source = port_u32(&port, 0, texts[index][1]);
        port_set32(&port, ebp, -0x360u, edi);
        esi = copy_text(&port, edi, source);
    }
    port_call_with(&port, 0x429460, settings, file, 0x5332bc, body + 0x80, esi, edi, ebp);
    port_set32(&port, ebp, -0x20u, 0);
    port_call_with(&port, 0x429350, settings, 0, 0x5332bc, body + 0x80, esi, 0, ebp);
    port_set32(&port, ebp, -0x20u, 0);
    port.env.chain = port_u32(&port, record, 0);
    return port_return(&port, port_u32(&port, record, 0), entry->edx);
}
