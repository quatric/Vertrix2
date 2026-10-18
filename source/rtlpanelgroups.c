#include "rtlpanelgroups.h"

/* Framed panels and their captions. */

/* The registers 0x470d20 carries from one part to the next. */
typedef struct PanelRegisters
{
    uint32_t eax;
    uint32_t edx;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t esi;
    uint32_t edi;
    uint32_t ebp;
} PanelRegisters;

static uint32_t call_frame(Port *port, uint32_t target, uint32_t eax, uint32_t edx, uint32_t ebx,
                           uint32_t ecx, uint32_t esi, uint32_t edi, uint32_t ebp,
                           const uint32_t *stack, unsigned count)
{
    return port_call_registers(port, target, eax, edx, ebx, ecx, esi, edi, ebp, stack, count);
}

static uint32_t call(Port *port, PanelRegisters *r, uint32_t target, uint32_t eax, uint32_t edx,
                     const uint32_t *stack, unsigned count)
{
    r->eax =
        call_frame(port, target, eax, edx, r->ebx, r->ecx, r->esi, r->edi, r->ebp, stack, count);
    r->edx = vertrix_lift_edx;
    return r->eax;
}

static uint32_t word_at(Port *port, uint32_t address)
{
    return (uint32_t)(int32_t)(int16_t)port_u16(port, 0, address);
}

/* A sprite of `size` bytes made by `make` and placed (0x4adf20 at 0). */
static uint32_t panel_sprite(Port *port, PanelRegisters *r, uint32_t size, uint32_t make)
{
    uint32_t zeros[5] = {0, 0, 0, 0, 0};
    uint32_t eax = call(port, r, 0x4ca000, size, r->edx, NULL, 0);
    if (eax != 0)
    {
        eax = call(port, r, make, eax, r->edx, NULL, 0);
    }
    r->esi = eax;
    r->ebx = 0;
    r->ecx = 0;
    call(port, r, 0x4adf20, eax, 0, zeros, 5);
    return eax;
}

/* A framed box (0x308 bytes, 0x4b2400) round the rectangle at `rect` (across, down, wide, high
 * words) with the text `text` (0x4b25b0 in the font 0x4f9c02, its height less 14), shown with 2,
 * +0x52 9, +0x4e 40, +0x93 1, +0x94 1, +0x95 1, +0x48 -20, and added to 0x54671c. */
static void panel_box(Port *port, PanelRegisters *r, uint32_t text, uint32_t rect)
{
    uint32_t box = panel_sprite(port, r, 0x308, 0x4b2400);
    uint32_t args[10];
    call(port, r, 0x4ac7b0, box, 2, NULL, 0);
    args[0] = word_at(port, rect + 4);
    args[1] = word_at(port, rect + 8);
    args[2] = (uint32_t)(int32_t)(int16_t)(port_u16(port, 0, rect + 0xc) - 0xe);
    args[3] = 2;
    args[4] = 2;
    args[5] = 0;
    args[6] = 0;
    args[7] = 1;
    args[8] = 1;
    args[9] = 1;
    port_set8(port, box, 0x52, 9);
    port_set8(port, box, 0x4e, 0x28);
    port_set8(port, box, 0x93, 1);
    port_set8(port, box, 0x94, 1);
    port_set8(port, box, 0x95, 1);
    port_set16(port, box, 0x48, 0xffec);
    r->ebx = (uint32_t)(int32_t)(int8_t)port_u8(port, 0, 0x4f9c02);
    r->ecx = word_at(port, rect);
    call(port, r, 0x4b25b0, box, text, args, 10);
    call(port, r, 0x4b5e70, 0x54671c, box, NULL, 0);
}

/* A caption (0x180 bytes, 0x4b6350) of the text `text` in the font 0x54001c set in the rectangle
 * at `rect` (0x4b65d0 with its right and its bottom less 14 and 1), shown with 2, +0x44 6, +0x93
 * 1, +0x94 1, +0x95 5, and added to 0x54671c. */
static void panel_caption(Port *port, PanelRegisters *r, uint32_t text, uint32_t rect)
{
    uint32_t caption = panel_sprite(port, r, 0x180, 0x4b6350);
    uint32_t bottom = port_u16(port, 0, rect + 4) + port_u16(port, 0, rect + 0xc);
    uint32_t args[3];
    args[0] =
        (uint32_t)(int32_t)(int16_t)(port_u16(port, 0, rect) + port_u16(port, 0, rect + 8) - 1);
    args[1] = (uint32_t)(int32_t)(int16_t)(bottom - 0xe);
    args[2] = (uint32_t)(int32_t)(int16_t)(bottom - 1);
    r->ebx = (uint32_t)(int32_t)(int8_t)port_u8(port, 0, 0x54001c);
    r->ecx = word_at(port, rect);
    call(port, r, 0x4b65d0, caption, text, args, 3);
    call(port, r, 0x4ac7b0, caption, 2, NULL, 0);
    port_set8(port, caption, 0x44, 6);
    port_set8(port, caption, 0x93, 1);
    port_set8(port, caption, 0x94, 1);
    port_set8(port, caption, 0x95, 5);
    call(port, r, 0x4b5e70, 0x54671c, caption, NULL, 0);
}

/* Original 0x470d20: the panel group for the texts eax and edx (framed boxes round the
 * rectangles 0x4f8800 and 0x4f8810, panel_box) and the captions ebx and ecx (set in the same
 * rectangles, panel_caption): the box for eax, the caption ebx, the box for edx and the caption
 * ecx, each made only for a text given. */
uint32_t vertrix_port_panel_group_470d20(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x18
    };
    Port port;
    PanelRegisters r;
    uint32_t ebp = entry->esp - 4;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->esi);
    port_set32(&port, ebp, -8u, entry->edi);
    port_set32(&port, ebp, -0xcu, entry->eax);
    port_set32(&port, ebp, -0x10u, entry->edx);
    port_set32(&port, ebp, -0x14u, entry->ebx);
    r.eax = entry->eax;
    r.edx = entry->edx;
    r.ebx = entry->ebx;
    r.ecx = entry->ecx;
    r.esi = entry->esi;
    r.edi = entry->ecx;
    r.ebp = ebp;
    if (entry->eax != 0)
    {
        panel_box(&port, &r, port_u32(&port, ebp, -0xcu), 0x4f8800);
    }
    if (port_u32(&port, ebp, -0x14u) != 0)
    {
        panel_caption(&port, &r, port_u32(&port, ebp, -0x14u), 0x4f8800);
    }
    if (port_u32(&port, ebp, -0x10u) != 0)
    {
        panel_box(&port, &r, port_u32(&port, ebp, -0x10u), 0x4f8810);
    }
    if (r.edi != 0)
    {
        panel_caption(&port, &r, r.edi, 0x4f8810);
    }
    return port_return(&port, r.eax, r.edx);
}
