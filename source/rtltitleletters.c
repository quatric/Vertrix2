#include "rtltitleletters.h"

/* The countdown letter of the title. */

/* A call (with count stack arguments, nearest first) that leaves its eax and edx in *eax and
 * *edx; the eax. */
static uint32_t letter_call(Port *port, uint32_t *eax, uint32_t *edx, uint32_t target, uint32_t a,
                            uint32_t d, uint32_t ebx, uint32_t ecx, uint32_t esi, uint32_t edi,
                            uint32_t ebp, const uint32_t *stack, unsigned count)
{
    *eax = port_call_registers(port, target, a, d, ebx, ecx, esi, edi, ebp, stack, count);
    *edx = vertrix_lift_edx;
    return *eax;
}

/* Original 0x4713d0 (guarded 0x516264): the countdown letter for the player eax: an actor of
 * 0x15c bytes (0x4ca000, made by 0x4abd70 with 2) and the text 0x50e62c printed with 3
 * (0x4cdfb0 into a string made by 0x4ca070). Player 1 sets 2 at what the print left in edx (+4)
 * and is placed by 0x4f8a48/0x4f8a4c, else 1 there and 0x4f8a50/0x4f8a54 (x + 0x3c, y + 0x9c).
 * The actor set up (0x4adf20 with five zeros), its glyph the text's first letter in the font
 * 0x4f9c05 (0x43f420, 0x4ac950), drawn (0x4ac8a0); +0xc 0, +0x94 1, +0x95 4, +0x93 1, +0x4e
 * 0x32, its spot and place the x and y, handed 0x459be0 (0x4ac8f0), aimed 0x3c from its spot
 * (0x4ad510), +0x30 0x3c, +0x24 0, +0x28 0x14, +0x32 1, 0x4ac7d0 with 10, 0x4ac510, +0x58 3,
 * +0x5c 0, +0x60 1, +0x44 0, added to 0x54671c (0x4b5e70); the string freed (0x4ca210). eax the
 * restored chain, edx kept. */
uint32_t vertrix_port_title_countdown_letter_4713d0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x38
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t record = ebp - 0x34;
    uint32_t player = entry->eax;
    uint32_t eax;
    uint32_t edx = 0x4ec1ec;
    uint32_t ebx = 0x516264;
    uint32_t ecx = player;
    uint32_t esi = 0;
    uint32_t edi = 1;
    uint32_t args[5];
    uint32_t y;
#define CALL(target, a, d)                                                                         \
    letter_call(&port, &eax, &edx, target, a, d, ebx, ecx, esi, edi, ebp, NULL, 0)
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    port_set32(&port, ebp, -0x14u, entry->edi);
    port_set32(&port, record, 0, port.env.chain);
    port.env.chain = record;
    port_set32(&port, ebp, -0x30u, edx);
    port_set32(&port, ebp, -0x2cu, ebx);
    port_set32(&port, ebp, -0x28u, esi);
    CALL(0x4ca070, ebp - 0x20, edx);
    port_set32(&port, ebp, -0x28u, edi);
    if (CALL(0x4ca000, 0x15c, edx) != 0)
    {
        port_set32(&port, ebp, -0x1cu, eax);
        port_set32(&port, ebp, -0x28u, 2);
        CALL(0x4abd70, eax, 2);
        port_set32(&port, ebp, -0x28u, edi);
        edx = eax;
    }
    else
    {
        edx = esi;
    }
    esi = edx;
    args[0] = ebp - 0x20;
    args[1] = 0x50e62c;
    args[2] = 3;
    letter_call(&port, &eax, &edx, 0x4cdfb0, ebp - 0x20, edx, ebx, ecx, esi, edi, ebp, args, 3);
    if (ecx == 1)
    {
        eax = port_u32(&port, 0, 0x4f8a48);
        port_set32(&port, edx, 4, 2);
        edx = port_u32(&port, 0, 0x4f8a4c);
    }
    else
    {
        eax = port_u32(&port, 0, 0x4f8a50);
        port_set32(&port, edx, 4, 1);
        edx = port_u32(&port, 0, 0x4f8a54);
    }
    edi = eax + 0x3c;
    y = edx + 0x9c;
    ecx = 0;
    ebx = 0;
    port_set32(&port, ebp, -0x18u, y);
    args[0] = args[1] = args[2] = args[3] = args[4] = 0;
    letter_call(&port, &eax, &edx, 0x4adf20, esi, 0, ebx, ecx, esi, edi, ebp, args, 5);
    CALL(0x43f420, (uint32_t)(int32_t)(int8_t)port_u8(&port, 0, 0x4f9c05),
         port_u8(&port, port_u32(&port, ebp, -0x20u), 0));
    CALL(0x4ac950, esi, eax);
    CALL(0x4ac8a0, esi, edx);
    port_set16(&port, esi, 0xc, 0);
    port_set8(&port, esi, 0x94, 1);
    port_set8(&port, esi, 0x95, 4);
    port_set8(&port, esi, 0x93, 1);
    port_set8(&port, esi, 0x4e, 0x32);
    port_set16(&port, esi, 8, edi);
    port_set16(&port, esi, 0xa, y);
    port_set16(&port, esi, 0x16, y);
    port_set16(&port, esi, 0xe, edi);
    CALL(0x4ac8f0, esi, 0x459be0);
    ecx = (uint32_t)(int32_t)(int16_t)port_u16(&port, esi, 0xa);
    ebx = (uint32_t)(int32_t)(int16_t)port_u16(&port, esi, 8);
    CALL(0x4ad510, esi, 0x3c);
    port_set16(&port, esi, 0x30, 0x3c);
    port_set16(&port, esi, 0x24, 0);
    port_set16(&port, esi, 0x28, 0x14);
    port_set16(&port, esi, 0x32, 1);
    CALL(0x4ac7d0, esi, 0xa);
    CALL(0x4ac510, esi, edx);
    port_set32(&port, esi, 0x58, 3);
    port_set32(&port, esi, 0x5c, 0);
    port_set32(&port, esi, 0x60, 1);
    port_set8(&port, esi, 0x44, 0);
    CALL(0x4b5e70, 0x54671c, esi);
    esi = 0;
    port_set32(&port, ebp, -0x28u, esi);
    CALL(0x4ca210, ebp - 0x20, 0);
#undef CALL
    eax = port_u32(&port, record, 0);
    port_set32(&port, ebp, -0x28u, esi);
    port.env.chain = eax;
    return port_return(&port, eax, entry->edx);
}
