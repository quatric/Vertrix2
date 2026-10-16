#include "port_rtloptionpanels.h"

/* The options panel. */

typedef struct
{
    Port *port;
    uint32_t eax;
    uint32_t edx;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t esi;
    uint32_t edi;
    uint32_t ebp;
} Panel;

enum
{
    TEXT = 0x540350,
    TOP = 0x54034c,
    LEFT = 0x540348,
    STYLE = 0x540378,
    FILL = 0x54037c,
    BORDER = 0x540380,
    SURFACE = 0x558c7c
};

/* A call (with count stack arguments, nearest first) of the tracked registers. */
static void panel_call(Panel *p, uint32_t target, const uint32_t *stack, unsigned count)
{
    vertrix_lift_in_esi = p->esi;
    vertrix_lift_in_edi = p->edi;
    vertrix_lift_in_ebp = p->ebp;
    p->eax =
        lift_call_arguments(&p->port->env, target, p->eax, p->edx, p->ebx, p->ecx, stack, count);
    vertrix_lift_in_esi = vertrix_lift_in_edi = vertrix_lift_in_ebp = 0;
    p->edx = vertrix_lift_edx;
}

static uint32_t g(Panel *p, uint32_t address)
{
    return port_u32(p->port, 0, address);
}

/* The text at esi copied to the buffer at edi two bytes a step (the original's inline copy): esi
 * left past the last step, al the terminator. */
static void copy_text(Panel *p)
{
    uint32_t to = p->edi;
    uint32_t value;
    while (!p->port->env.failed)
    {
        value = port_u8(p->port, p->esi, 0);
        port_set8(p->port, to, 0, value);
        if (value == 0)
        {
            break;
        }
        value = port_u8(p->port, p->esi, 1);
        p->esi += 2;
        port_set8(p->port, to, 1, value);
        to += 2;
        if (value == 0)
        {
            break;
        }
    }
    p->eax &= ~0xffu;
}

/* The style 5, or 6 when the flag is clear (5 + whether the value is 0). */
static void style_of(Panel *p, uint32_t clear)
{
    p->eax = (clear ? 1u : 0u) + 5;
    port_set32(p->port, 0, STYLE, p->eax);
}

/* A text from the buffer drawn (0x4429a0) at the stack row: TOP + 2. */
static void draw_text(Panel *p)
{
    uint32_t row[1];
    row[0] = g(p, TOP) + 2;
    p->eax = g(p, SURFACE);
    panel_call(p, 0x4429a0, row, 1);
}

/* A box (0x47bd80) of the rows, the fill and the border. */
static void draw_box(Panel *p, uint32_t rows)
{
    uint32_t box[3];
    box[0] = rows;
    box[1] = g(p, FILL);
    box[2] = g(p, BORDER);
    p->eax = g(p, SURFACE);
    panel_call(p, 0x47bd80, box, 3);
}

/* The label at the text drawn in the style at the left + 2. */
static void label(Panel *p, uint32_t text)
{
    p->esi = text;
    p->edi = TEXT;
    p->ebx = 0;
    copy_text(p);
    p->ecx = g(p, LEFT) + 2;
    p->ebx = (p->ebx & ~0xffu) | port_u8(p->port, 0, STYLE);
    p->edx = p->edi;
    draw_text(p);
}

/* The value text drawn in the style at the left + width + 3 (edi then as given). */
static void value_text(Panel *p, uint32_t width, uint32_t edi)
{
    p->edx = TEXT;
    p->ecx = g(p, LEFT) + width + 3;
    p->ebx = port_u8(p->port, 0, STYLE);
    p->edi = edi;
    draw_text(p);
}

/* A count printed into 0x540370 (0x4cdfb0 with the format) or, above 9999 or at 0, the fixed
 * text (0x4ca370). */
static void count_text(Panel *p, uint32_t count, uint32_t format, uint32_t zero, uint32_t many)
{
    if (count != 0 && count <= 0x270f)
    {
        uint32_t args[3] = {0x540370, format, count};
        panel_call(p, 0x4cdfb0, args, 3);
    }
    else
    {
        p->edx = count == 0 ? zero : many;
        p->eax = 0x540370;
        panel_call(p, 0x4ca370, NULL, 0);
    }
}

/* The text 0x540370 copied to the buffer. */
static void copy_count(Panel *p)
{
    p->edi = TEXT;
    p->esi = g(p, 0x540370);
    copy_text(p);
}

/* Original 0x41d6d0: the options panel drawn on the surface 0x558c7c. Once (0x4d66cd of
 * 0x540384) its text 0x540370 made (0x4ca070, 0x4ec1f7 of 0x4f9d60); then, only in the options
 * (0x532a08 1): a box (0x47bd80, 0x6b by 0x1c in 0x54d5f4, no border), and in rows (0x54034c)
 * from the left 0x540348 the labels and values (0x4429a0, copied to 0x540350; the style 0x540378
 * 5, or 6 when off, the value 4 or 6, or 3 or 6) of 0x532a0c, 0x532b4c (on when not 20), the
 * colour boxes (0x47bd80, 14 rows) with 0x532a04 (0x4777c0), the count 0x532a10 and the count
 * 0x532a14 (kept at 0x540374), each printed (0x4cdfb0) or fixed (0x4ca370). eax as the last draw
 * left it, edx kept. */
uint32_t vertrix_port_options_panel_41d6d0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x28
    };
    Port port;
    uint8_t stack[BELOW + 8];
    Panel p;
    uint32_t box[3];
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    p.port = &port;
    p.eax = entry->eax;
    p.edx = entry->edx;
    p.ebx = entry->ebx;
    p.ecx = entry->ecx;
    p.esi = entry->esi;
    p.edi = entry->edi;
    p.ebp = entry->esp - 4;
    port_set32(&port, p.ebp, 0, entry->ebp);
    port_set32(&port, p.ebp, -4u, entry->ebx);
    port_set32(&port, p.ebp, -8u, entry->ecx);
    port_set32(&port, p.ebp, -0xcu, entry->edx);
    port_set32(&port, p.ebp, -0x10u, entry->esi);
    port_set32(&port, p.ebp, -0x14u, entry->edi);
    p.edx = 1;
    p.eax = 0x540384;
    panel_call(&p, 0x4d66cd, NULL, 0);
    if (p.eax == 0)
    {
        p.eax = 0x540370;
        panel_call(&p, 0x4ca070, NULL, 0);
        p.eax = 0x4f9d60;
        panel_call(&p, 0x4ec1f7, NULL, 0);
    }
    if (g(&p, 0x532a08) != 1)
    {
        return port_return(&port, p.eax, entry->edx);
    }
    port_set8(&port, p.ebp, -0x1cu, 0x32);
    port_set8(&port, p.ebp, -0x18u, 0x38);
    port_set32(&port, 0, BORDER, 0xff000000u);
    port_set32(&port, 0, LEFT, 1);
    port_set32(&port, 0, FILL, g(&p, 0x54d5f4));
    port_set32(&port, 0, TOP, 1);
    box[0] = 0x1c;
    box[1] = g(&p, 0x54d5f4);
    box[2] = 0xff000000u;
    p.ecx = 0x6b;
    p.edx = 1;
    p.ebx = 1;
    p.eax = g(&p, SURFACE);
    panel_call(&p, 0x47bd80, box, 3);
    style_of(&p, g(&p, 0x532a0c) == 0);
    label(&p, 0x50dcc7);
    port_set32(&port, 0, STYLE, g(&p, 0x532a0c) != 0 ? 4 : 6);
    p.esi = 0x50dcd0;
    p.edi = TEXT;
    copy_text(&p);
    value_text(&p, 0x32, g(&p, LEFT));
    port_set32(&port, 0, TOP, g(&p, TOP) + 0xd);
    style_of(&p, g(&p, 0x532b4c) != 0x14);
    label(&p, 0x50dcdb);
    port_set32(&port, 0, STYLE, g(&p, 0x532b4c) == 0x14 ? 4 : 6);
    p.esi = 0x50dce6;
    p.edi = TEXT;
    copy_text(&p);
    port_set32(&port, p.ebp, -0x20u, 0x32);
    value_text(&p, 0x32, TEXT);
    port_set32(&port, 0, TOP, g(&p, TOP) + 0x10);
    port_set32(&port, p.ebp, -0x24u, 0x32);
    p.edx = g(&p, LEFT);
    p.ebx = g(&p, TOP);
    p.ecx = 0x32;
    p.esi = 0x50dcf1;
    draw_box(&p, 0xe);
    copy_text(&p);
    p.ebx = 5;
    p.ecx = g(&p, LEFT) + 2;
    p.edx = p.edi;
    p.edi = 0x32;
    draw_text(&p);
    p.ecx = 0x38;
    p.edx = g(&p, LEFT) + p.edi + 1;
    p.edi = TEXT;
    p.ebx = g(&p, TOP);
    p.esi = 0x50dcf5;
    draw_box(&p, 0xe);
    copy_text(&p);
    p.edx = g(&p, 0x532a04);
    p.eax = p.edi;
    panel_call(&p, 0x4777c0, NULL, 0);
    p.ebx = 3;
    p.ecx = g(&p, LEFT) + 0x32 + 3;
    p.edx = p.edi;
    draw_text(&p);
    p.ebx = g(&p, TOP) + 0xf;
    p.edx = g(&p, LEFT);
    p.ecx = 0x32;
    port_set32(&port, 0, TOP, p.ebx);
    draw_box(&p, 0xe);
    style_of(&p, g(&p, 0x532a10) == 0);
    label(&p, 0x50dcf6);
    p.edi = g(&p, BORDER);
    p.ebx = g(&p, TOP);
    p.edx = g(&p, LEFT) + 0x33;
    p.ecx = 0x38;
    draw_box(&p, 0xe);
    p.ecx = g(&p, 0x532a10);
    count_text(&p, p.ecx, 0x50dd04, 0x50dcfb, 0x50dd0a);
    copy_count(&p);
    port_set32(&port, 0, STYLE, g(&p, 0x532a10) != 0 ? 3 : 6);
    value_text(&p, 0x32, TEXT);
    port_set32(&port, 0, 0x540374, g(&p, 0x532a14));
    port_set32(&port, 0, TOP, g(&p, TOP) + 0xf);
    p.esi = g(&p, BORDER);
    p.edi = g(&p, FILL);
    p.edx = g(&p, LEFT);
    p.ecx = 0x32;
    p.ebx = g(&p, TOP);
    draw_box(&p, 0xe);
    style_of(&p, g(&p, 0x540374) == 0);
    label(&p, 0x50dd12);
    p.esi = g(&p, LEFT);
    p.edx = g(&p, LEFT) + 0x33;
    p.ecx = 0x38;
    p.ebx = g(&p, TOP);
    draw_box(&p, 0xe);
    p.edi = g(&p, 0x540374);
    count_text(&p, p.edi, 0x50dd23, 0x50dd1a, 0x50dd29);
    port_set32(&port, 0, STYLE, g(&p, 0x540374) != 0 ? 3 : 6);
    copy_count(&p);
    value_text(&p, 0x32, g(&p, LEFT));
    port_set32(&port, 0, TOP, g(&p, TOP) + 0xf);
    return port_return(&port, p.eax, entry->edx);
}
