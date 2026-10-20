#include "dos.h"

/* The I/O port map: which device answers each port the program reads or writes. A 16-bit or
 * 32-bit access is consecutive byte accesses, as on the ISA bus (the program writes a VGA
 * index and its value with one `out dx, ax`). */

static uint32_t sb_base = 0x220;

static uint32_t in8(uint32_t port)
{
    if (port < 0x10 || (port >= 0x80 && port < 0x90) || (port >= 0xc0 && port < 0xe0))
    {
        return v1_dma_read(port);
    }
    switch (port)
    {
        case 0x20:
        case 0x21:
        case 0xa0:
        case 0xa1:
            return v1_pic_read(port);
        case 0x40:
        case 0x41:
        case 0x42:
        case 0x43:
            return v1_pit_read(port);
        case 0x60:
        case 0x61:
        case 0x64:
            return v1_keyboard_read(port);
        case 0x201:
            /* The game port with nothing on it: no buttons, the axes never time out. */
            return 0xf0;
        case 0x388:
        case 0x389:
            /* No AdLib. */
            return 0xff;
    }
    if (port >= 0x3b0 && port < 0x3e0)
    {
        return v1_vga_port_read(port);
    }
    if (port >= sb_base && port < sb_base + 0x10)
    {
        return v1_sb_read(port - sb_base);
    }
    v1_log_once("in from port %03x", port);
    return 0xff;
}

static void out8(uint32_t port, uint32_t value)
{
    value &= 0xffu;
    if (port < 0x10 || (port >= 0x80 && port < 0x90) || (port >= 0xc0 && port < 0xe0))
    {
        v1_dma_write(port, value);
        return;
    }
    switch (port)
    {
        case 0x20:
        case 0x21:
        case 0xa0:
        case 0xa1:
            v1_pic_write(port, value);
            return;
        case 0x40:
        case 0x41:
        case 0x42:
        case 0x43:
            v1_pit_write(port, value);
            return;
        case 0x60:
        case 0x61:
        case 0x64:
            v1_keyboard_write(port, value);
            return;
        case 0x201:
        case 0x388:
        case 0x389:
            return;
    }
    if (port >= 0x3b0 && port < 0x3e0)
    {
        v1_vga_port_write(port, value);
        return;
    }
    if (port >= sb_base && port < sb_base + 0x10)
    {
        v1_sb_write(port - sb_base, value);
        return;
    }
    v1_log_once("out %02x to port %03x", value, port);
}

uint32_t v1_in(Cpu *c, uint32_t port, unsigned size)
{
    (void)c;
    port &= 0xffffu;
    uint32_t value = 0;
    for (unsigned i = 0; i < size; ++i)
    {
        value |= in8(port + i) << (8 * i);
    }
    return value;
}

void v1_out(Cpu *c, uint32_t port, uint32_t value, unsigned size)
{
    (void)c;
    port &= 0xffffu;
    for (unsigned i = 0; i < size; ++i)
    {
        out8(port + i, value >> (8 * i));
    }
}
