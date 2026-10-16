#include "port_rtlsettingloads.h"

/* Game settings loaded. */

/* Original 0x415580 (guarded 0x513a14): the settings loaded: 0x532b3c from 0x4895e0 of 0x50d395
 * and 0x4895e0 of 0x50d3a2 with 0x4fd310; 0x532b38, 0x532b40, 0x532b44, 0x532b48 and the byte
 * 0x532a34 cleared, 0x532b94 0x3d and 0x532b90 0x3c; the file name 0x4fd310 with 0x50d3af made
 * in the frame (0x45f540), a settings record given its defaults (0x4290c0) and read (0x429530),
 * and its body (0x429660) copied to the game: +0..+0x14 to 0x532b4c and 0x532b54..0x532b64, the
 * keys +0x18..+0x28 to 0x532b6c..0x532b7c, +0x44/+0x48 to 0x532b80/0x532b84, +0x2c..+0x40 to
 * 0x532b98..0x532bac, +0x4c to 0x532b88, +0x50/+0x54 to 0x532bb4/0x532bb8, the five +0x58 to
 * 0x533294 and the five texts +0x6c on to 0x5332a8 (0x4ca370); 0x532b50 and 0x532b68 copied
 * from 0x532b4c and 0x532b64, 0x532bb0 0, +0x80..+0x90 to 0x532bd4..0x532be4, 0x532b34 10, and
 * the texts +0x94, +0xf8, +0x15c and +0x1c0 to 0x532be8..0x532bf4; 0x532b88 1 when 0x532b3c or
 * 0x532b38 is 1; the record released (0x429350). eax the restored chain, edx kept. */
uint32_t vertrix_port_settings_load_415580(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x35c
    };
    static const uint32_t first[][2] = {{0x0, 0x532b4c}, {0x4, 0x532b54},  {0x8, 0x532b58},
                                        {0xc, 0x532b5c}, {0x10, 0x532b60}, {0x14, 0x532b64}};
    static const uint32_t later[][2] = {{0x44, 0x532b80}, {0x48, 0x532b84}, {0x2c, 0x532b98},
                                        {0x30, 0x532b9c}, {0x34, 0x532ba0}, {0x38, 0x532ba4},
                                        {0x3c, 0x532ba8}, {0x40, 0x532bac}, {0x4c, 0x532b88},
                                        {0x50, 0x532bb4}, {0x54, 0x532bb8}};
    static const uint32_t tail[][2] = {{0x80, 0x532bd4}, {0x84, 0x532bd8}, {0x88, 0x532bdc}};
    static const uint32_t texts[4][2] = {
        {0x94, 0x532be8}, {0xf8, 0x532bec}, {0x15c, 0x532bf0}, {0x1c0, 0x532bf4}};
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t record = ebp - 0x28;
    uint32_t settings = ebp - 0x358;
    uint32_t body;
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
    port_set32(&port, ebp, -0x24u, 0x4ec1ec);
    port_set32(&port, ebp, -0x20u, 0x513a14);
    port_set32(&port, ebp, -0x1cu, 0);
    port_set32(
        &port, 0, 0x532b3c,
        port_call_with(&port, 0x4895e0, 0x50d395, 0x4ec1ec, 0, 0x513a14, 1, entry->edi, ebp));
    port_call_with(&port, 0x4895e0, 0x50d3a2, 0x4fd310, 0, 0x3c, 1, entry->edi, ebp);
    port_set32(&port, 0, 0x532b38, 0);
    port_set32(&port, 0, 0x532b40, 0);
    port_set32(&port, 0, 0x532b44, 0);
    port_set32(&port, 0, 0x532b48, 0);
    port_set8(&port, 0, 0x532a34, 0);
    port_set32(&port, 0, 0x532b94, 0x3d);
    port_set32(&port, 0, 0x532b90, 0x3c);
    port_call_with(&port, 0x45f540, ebp - 0x12c, vertrix_lift_edx, 0x50d3af, 0x3c, 1, entry->edi,
                   ebp);
    port_call_with(&port, 0x4290c0, settings, ebp - 0x12c, 0x50d3af, 0x3c, 1, entry->edi, ebp);
    port_set32(&port, ebp, -0x1cu, 1);
    port_call_with(&port, 0x429530, settings, vertrix_lift_edx, 0x50d3af, 0x3c, 1, entry->edi, ebp);
    body = port_call_with(&port, 0x429660, settings, vertrix_lift_edx, 0x50d3af, 0x3c, 1,
                          entry->edi, ebp);
    for (index = 0; index < sizeof first / sizeof first[0]; index++)
    {
        port_set32(&port, 0, first[index][1], port_u32(&port, body, first[index][0]));
    }
    for (index = 0; index < 9; index++)
    {
        port_set16(&port, 0, 0x532b6c + index * 2, port_u16(&port, body, 0x18 + index * 2));
    }
    for (index = 0; index < sizeof later / sizeof later[0]; index++)
    {
        port_set32(&port, 0, later[index][1], port_u32(&port, body, later[index][0]));
    }
    for (index = 0; index < 5; index++)
    {
        port_set32(&port, 0, 0x533294 + index * 4, port_u32(&port, body, 0x58 + index * 4));
    }
    for (index = 0; index < 5 && !port.env.failed; index++)
    {
        uint32_t text = body + 0x6c + index * 4;
        port_call_with(&port, 0x4ca370, 0x5332a8 + index * 4, text, 0x5332a8 + index * 4, text,
                       body + 0x80, body, ebp);
    }
    port_set32(&port, 0, 0x532b50, port_u32(&port, 0, 0x532b4c));
    port_set32(&port, 0, 0x532b68, port_u32(&port, 0, 0x532b64));
    port_set32(&port, 0, 0x532bb0, 0);
    for (index = 0; index < sizeof tail / sizeof tail[0]; index++)
    {
        port_set32(&port, 0, tail[index][1], port_u32(&port, body, tail[index][0]));
    }
    port_set32(&port, 0, 0x532b34, 0xa);
    port_set32(&port, 0, 0x532be0, port_u32(&port, body, 0x8c));
    port_set32(&port, 0, 0x532be4, port_u32(&port, body, 0x90));
    for (index = 0; index < 4 && !port.env.failed; index++)
    {
        port_call_with(&port, 0x4ca370, texts[index][1], body + texts[index][0], 0x5332bc,
                       body + 0x80, body + 0x80, body, ebp);
    }
    if (port_u32(&port, 0, 0x532b3c) == 1 || port_u32(&port, 0, 0x532b38) == 1)
    {
        port_set32(&port, 0, 0x532b88, 1);
    }
    port_set32(&port, ebp, -0x1cu, 0);
    port_call_with(&port, 0x429350, settings, 0, 0x5332bc, body + 0x80, body + 0x80, 0, ebp);
    port_set32(&port, ebp, -0x1cu, 0);
    port.env.chain = port_u32(&port, record, 0);
    return port_return(&port, port_u32(&port, record, 0), entry->edx);
}
