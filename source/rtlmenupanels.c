#include "rtlmenupanels.h"

/* Menu panels with their entries. */

static uint32_t call_frame(Port *port, uint32_t target, uint32_t eax, uint32_t edx, uint32_t ebx,
                           uint32_t ecx, uint32_t esi, uint32_t edi, uint32_t ebp,
                           const uint32_t *stack, unsigned count)
{
    return port_call_registers(port, target, eax, edx, ebx, ecx, esi, edi, ebp, stack, count);
}

/* Original 0x4657f0 (guarded 0x515ab8): the menu panel (0x160 bytes, 0x4ca000; 0x4b5400 makes
 * it) placed (0x4adf20 at 0) and sized (0x4b54d0) 0xdc by 0x6e at 2 across and one below the word
 * 0x4f88ac; +0x48 0, shown (0x4ac7b0 with 2), +0x110 1, 0x4ac4e0 with 0x7f, clipped to 0..0x27f
 * across and 0x4f88ac..0x1df down, +0x8e 3, stepped by 0x443460 (0x4ac8f0), 0x4ac930 with 0,
 * drawn by 0x4568c0 (0x4ac910), 0x4719a0, and added to 0x546730 (0x4b5e70). Then its five entries
 * made (0x470b20 with their numbers and the texts 0x50e4bb, 0x50e4ca, 0x50e4d9, 0x50e4e8 and
 * 0x50e4f7), stepped by 0x4560c0, 0x4564e0, 0x4566d0, 0x456300 and 0x4560c0, drawn by 0x4568c0,
 * the first with +0x15c 1 and +0x14c from 0x4f7bc0, the last with +0x14c from 0x4f7bc4, each
 * given 0x4719a0 and added to 0x546730. eax the restored chain, edx kept. */
uint32_t vertrix_port_menu_panel_make_4657f0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x38
    };
    static const uint32_t texts[5] = {0x50e4bb, 0x50e4ca, 0x50e4d9, 0x50e4e8, 0x50e4f7};
    static const uint32_t steps[5] = {0x4560c0, 0x4564e0, 0x4566d0, 0x456300, 0x4560c0};
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t record = ebp - 0x34;
    uint32_t zeros[5] = {0, 0, 0, 0, 0};
    uint32_t eax;
    uint32_t ebx = 0x6e;
    uint32_t ecx = 0x515ab8;
    uint32_t esi = entry->esi;
    uint32_t edi = 2;
    uint32_t panel;
    uint32_t index;
#define CALL(target, a, d) port_call_with(&port, target, a, d, ebx, ecx, esi, edi, ebp)
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    port_set32(&port, ebp, -0x14u, entry->edi);
    port_set32(&port, record, 0, port.env.chain);
    port.env.chain = record;
    port_set32(&port, ebp, -0x30u, 0x4ec1ec);
    port_set32(&port, ebp, -0x2cu, 0x515ab8);
    port_set32(&port, ebp, -0x28u, 0);
    port_set32(&port, ebp, -0x1cu, 0xdc);
    port_set16(&port, ebp, -0x20u, port_u16(&port, 0, 0x4f88ac) + 1);
    port_set32(&port, ebp, -0x18u, 0x6e);
    eax = CALL(0x4ca000, 0x160, 0xdc);
    if (eax != 0)
    {
        eax = CALL(0x4b5400, eax, vertrix_lift_edx);
    }
    panel = eax;
    esi = panel;
    call_frame(&port, 0x4adf20, panel, 0, 0, 0, esi, edi, ebp, zeros, 5);
    ebx = (uint32_t)(int32_t)(int16_t)port_u16(&port, ebp, -0x20u);
    ecx = port_u16(&port, ebp, -0x1cu);
    {
        uint32_t args[1] = {port_u16(&port, ebp, -0x18u)};
        call_frame(&port, 0x4b54d0, panel, (uint32_t)(int32_t)(int16_t)edi, ebx, ecx, esi, edi, ebp,
                   args, 1);
    }
    port_set16(&port, panel, 0x48, 0);
    CALL(0x4ac7b0, panel, 2);
    ebx = 0;
    port_set8(&port, panel, 0x110, 1);
    CALL(0x4ac4e0, panel, 0x7f);
    port_set16(&port, panel, 0xa8, 0);
    port_set16(&port, panel, 0xaa, 0x27f);
    port_set16(&port, panel, 0xae, 0x1df);
    port_set16(&port, panel, 0xac, port_u16(&port, 0, 0x4f88ac));
    port_set8(&port, panel, 0x8e, 3);
    CALL(0x4ac8f0, panel, 0x443460);
    CALL(0x4ac930, panel, 0);
    CALL(0x4ac910, panel, 0x4568c0);
    CALL(0x4719a0, panel, vertrix_lift_edx);
    CALL(0x4b5e70, 0x546730, panel);
    for (index = 0; index < 5 && !port.env.failed; index++)
    {
        uint32_t item = CALL(0x470b20, index, texts[index]);
        esi = item;
        CALL(0x4ac8f0, item, steps[index]);
        CALL(0x4ac910, item, 0x4568c0);
        if (index == 0)
        {
            port_set16(&port, item, 0x15c, 1);
            port_set32(&port, item, 0x14c, port_u32(&port, 0, 0x4f7bc0));
        }
        else if (index == 4)
        {
            port_set32(&port, item, 0x14c, port_u32(&port, 0, 0x4f7bc4));
        }
        if (index == 4)
        {
            CALL(0x4719a0, item, item);
            CALL(0x4b5e70, 0x546730, vertrix_lift_edx);
        }
        else
        {
            CALL(0x4719a0, item, vertrix_lift_edx);
            CALL(0x4b5e70, 0x546730, item);
        }
    }
#undef CALL
    port.env.chain = port_u32(&port, record, 0);
    return port_return(&port, port_u32(&port, record, 0), entry->edx);
}
