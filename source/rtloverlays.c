#include "rtloverlays.h"

/* Centred overlay sprites. */

static uint32_t call_frame(Port *port, uint32_t target, uint32_t eax, uint32_t edx, uint32_t ebx,
                           uint32_t ecx, uint32_t esi, uint32_t edi, uint32_t ebp,
                           const uint32_t *stack, unsigned count)
{
    return port_call_registers(port, target, eax, edx, ebx, ecx, esi, edi, ebp, stack, count);
}

/* Original 0x45f770 (guarded 0x515714): four sprites (0x15c bytes, 0x4ca000; 0x4abd70 makes each)
 * kept at 0x54670c, 0x546710, 0x546714 and 0x546718, each placed (0x4adf20 with 0x443260) at the
 * centre of the screen 0x5b9c8e/0x5b9c90 with the picture 0x5449c4 for the first and 0x5449e0 for
 * the rest, given 0x4ac7b0 5, 4, 4, 4 and 0x4ac470 5, 8, 4, 2; all but the first with +0x95 4,
 * +0x93 1 and +0x44 0x10. eax the restored chain, edx kept. */
uint32_t vertrix_port_overlay_sprites_make_45f770(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x30
    };
    static const uint32_t slots[4] = {0x54670c, 0x546710, 0x546714, 0x546718};
    static const uint32_t depths[4] = {5, 4, 4, 4};
    static const uint32_t speeds[4] = {5, 8, 4, 2};
    static const uint32_t states[4] = {1, 3, 5, 7};
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t record = ebp - 0x2c;
    uint32_t eax;
    uint32_t edx = 0x4ec1ec;
    uint32_t ebx = 0;
    uint32_t ecx = 0x515714;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    unsigned index;
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
    port_set32(&port, ebp, -0x28u, 0x4ec1ec);
    port_set32(&port, ebp, -0x24u, 0x515714);
    port_set32(&port, ebp, -0x20u, 0);
    for (index = 0; index < 4 && !port.env.failed; index++)
    {
        uint32_t sprite;
        eax = CALL(0x4ca000, 0x15c, edx);
        edx = vertrix_lift_edx;
        if (eax != 0)
        {
            uint32_t after = 0;
            port_set32(&port, ebp, -0x18u, eax);
            switch (index)
            {
                case 0:
                    esi = 1;
                    break;
                case 1:
                    edx = 3;
                    ecx = 0;
                    break;
                case 2:
                    ebx = 5;
                    esi = 0;
                    break;
                default:
                    edi = 7;
                    edx = 0;
                    break;
            }
            port_set32(&port, ebp, -0x20u, states[index]);
            eax = CALL(0x4abd70, eax, edx);
            if (index == 3)
            {
                after = vertrix_lift_edx;
            }
            port_set32(&port, ebp, -0x20u, after);
        }
        sprite = eax;
        ebx = port_u16(&port, 0, 0x5b9c90) >> 1;
        edx = port_u16(&port, 0, 0x5b9c8e) >> 1;
        ecx = 0;
        port_set32(&port, 0, slots[index], sprite);
        {
            uint32_t args[5] = {index == 0 ? 0x5449c4 : 0x5449e0, 0, 0, 0x443260, 0};
            call_frame(&port, 0x4adf20, sprite, edx, ebx, ecx, esi, edi, ebp, args, 5);
        }
        CALL(0x4ac7b0, port_u32(&port, 0, slots[index]), depths[index]);
        CALL(0x4ac470, port_u32(&port, 0, slots[index]), speeds[index]);
        edx = vertrix_lift_edx;
        if (index != 0)
        {
            sprite = port_u32(&port, 0, slots[index]);
            port_set8(&port, sprite, 0x95, 4);
            port_set8(&port, sprite, 0x93, 1);
            port_set8(&port, sprite, 0x44, 0x10);
        }
    }
#undef CALL
    port.env.chain = port_u32(&port, record, 0);
    return port_return(&port, port_u32(&port, record, 0), entry->edx);
}
