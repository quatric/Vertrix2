#include "rtlcolourbanks.h"

/* The colour banks. */

/* A call (with count stack arguments, nearest first) that leaves its edx in *edx; the eax. */
static uint32_t bank_call(Port *port, uint32_t *edx, uint32_t target, uint32_t eax, uint32_t d,
                          uint32_t ebx, uint32_t ecx, uint32_t esi, uint32_t edi, uint32_t ebp,
                          const uint32_t *stack, unsigned count)
{
    uint32_t result;
    result = port_call_registers(port, target, eax, d, ebx, ecx, esi, edi, ebp, stack, count);
    *edx = vertrix_lift_edx;
    return result;
}

/* The 13 shade colours (0x54b808, 100 or 50 a channel) and the 12 plain ones (0x54d5f4). */
static const uint32_t shades[13] = {
    0,          0x646400,   0x326400,   0x6400,     0x32006400, 0x64006400, 0x64003200,
    0x64000000, 0x64320000, 0x64640000, 0x32640000, 0x640000,   0x643200,
};
static const uint32_t plain[12] = {
    0, 0xff, 0xff00, 0xffff00, 0xff0000, 0xffff, 0xff00ff, 0xffffff, 0xff, 0xbf, 0x7f, 0x3f,
};

/* Original 0x474e00 (guarded 0x516424): the colour banks for the screen eax. A colour converter
 * at ebp - 0x54 made (0x481b20) for the masks 0xff0000, 0xff00, 0xff and 0xff000000 (0x481bc0;
 * none frees it, 0x481b30); the shades 0x54b808 and the plain colours 0x54d5f4 converted
 * (0x481e10); each shade's channels mapped through the table +0x190 of 0x54cdc8 (kept at
 * 0x54d5d0, the shade at 0x54d5d4) into 0x54b83c; the converter freed. eax the restored chain,
 * edx kept. */
uint32_t vertrix_port_colour_banks_build_474e00(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x58
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t record = ebp - 0x28;
    uint32_t converter = ebp - 0x54;
    uint32_t screen = entry->eax;
    uint32_t edx;
    uint32_t edi;
    uint32_t ebx;
    uint32_t index;
    uint32_t eax;
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
    port_set32(&port, ebp, -0x20u, 0x516424);
    port_set32(&port, ebp, -0x1cu, 0);
    bank_call(&port, &edx, 0x481b20, converter, 0x4ec1ec, 0, 0x516424, screen, 1, ebp, NULL, 0);
    port_set32(&port, ebp, -0x1cu, 1);
    for (index = 0; index < 13; index++)
    {
        port_set32(&port, 0, 0x54b808 + index * 4, shades[index]);
    }
    {
        uint32_t alpha[1] = {0xff000000u};
        eax = bank_call(&port, &edx, 0x481bc0, converter, 0xff0000, 0xff00, 0xff, screen,
                        0x64640000, ebp, alpha, 1);
    }
    if (eax == 0)
    {
        bank_call(&port, &edx, 0x481b30, converter, 0, 0xff00, 0xff, screen, 0x64640000, ebp, NULL,
                  0);
        eax = port_u32(&port, record, 0);
        port.env.chain = eax;
        return port_return(&port, eax, entry->edx);
    }
    for (index = 0; index < 13 && !port.env.failed; index++)
    {
        eax =
            bank_call(&port, &edx, 0x481e10, converter, screen,
                      port_u32(&port, 0, 0x54b808 + index * 4), index, screen, index, ebp, NULL, 0);
        port_set32(&port, 0, 0x54b808 + index * 4, eax);
    }
    for (index = 0; index < 12; index++)
    {
        port_set32(&port, 0, 0x54d5f4 + index * 4, plain[index]);
    }
    for (index = 0; index < 12 && !port.env.failed; index++)
    {
        eax =
            bank_call(&port, &edx, 0x481e10, converter, screen,
                      port_u32(&port, 0, 0x54d5f4 + index * 4), index, screen, index, ebp, NULL, 0);
        port_set32(&port, 0, 0x54d5f4 + index * 4, eax);
    }
    ebx = 0;
    edi = 0;
    for (index = 0; index < 13; index++)
    {
        uint32_t table = port_u32(&port, port_u32(&port, 0, 0x54cdc8), 0x190);
        uint32_t shade;
        port_set32(&port, 0, 0x54d5d0, table);
        shade = port_u32(&port, 0, 0x54b808 + index * 4);
        port_set32(&port, 0, 0x54d5d4, shade);
        edi = port_u8(&port, table + ((shade >> 24) & 0xff), 0) << 16;
        edi |= port_u8(&port, table + ((shade >> 16) & 0xff), 0) << 8;
        ebx = port_u8(&port, table + ((port_u16(&port, 0, 0x54d5d4) >> 8) & 0xff), 0);
        edi |= ebx;
        port_set32(&port, 0, 0x54b83c + index * 4, edi);
    }
    port_set32(&port, ebp, -0x1cu, 0);
    bank_call(&port, &edx, 0x481b30, converter, 0, ebx, 13, port_u32(&port, 0, 0x54d5d0), edi, ebp,
              NULL, 0);
    port_set32(&port, ebp, -0x1cu, 0);
    eax = port_u32(&port, record, 0);
    port.env.chain = eax;
    return port_return(&port, eax, entry->edx);
}
