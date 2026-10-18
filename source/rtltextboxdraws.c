#include "rtltextboxdraws.h"

enum
{
    /* The frame under the return slot and the measures in it (offsets below the return slot):
     * each pass's call to 0x4408e0 gets four, at its own places (A: the widest line, B: drawing,
     * C: the total height). */
    BELOW = 0x80,
    WIDTH_A = 0x80,
    HEIGHT_A = 0x7c,
    OUT_A3 = 0x54,
    OUT_A4 = 0x3c,
    WIDTH_B = 0x74,
    HEIGHT_B = 0x6c,
    OUT_B3 = 0x40,
    OUT_B4 = 0x4c,
    WIDTH_C = 0x78,
    HEIGHT_C = 0x70,
    OUT_C3 = 0x44,
    OUT_C4 = 0x50,

    /* The text box: its rectangle, the text and its lines (a style byte, the count, then the word
     * offsets and lengths of up to 100 lines), the paddings and the alignment flags. */
    BOX_LEFT = 0xe,
    BOX_TOP = 0x16,
    BOX_FONT = 0x44,
    BOX_WIDTH = 0xf4,
    BOX_HEIGHT = 0xf8,
    BOX_TEXT = 0x15c,
    BOX_STYLE = 0x160,
    BOX_LINES = 0x161,
    BOX_LINE_OFFSETS = 0x162,
    BOX_LINE_LENGTHS = 0x22a,
    PAD_LEFT = 0x2f2,
    PAD_RIGHT = 0x2f4,
    PAD_TOP = 0x2f6,
    PAD_BOTTOM = 0x2f8,
    ALIGN_LEFT = 0x2fc,
    ALIGN_MIDDLE = 0x300,
    ALIGN_CENTRE = 0x304,

    CLEAR_ALLOCATE = 0x4ec160,
    COPY_PADDED = 0x4eb860,
    MEASURE = 0x4408e0,
    DRAW_GLYPHS = 0x440a20,
    DRAW = 0x440ca0,
    FREE = 0x4ea190
};

typedef struct Box
{
    Port *port;
    const LiftEntry *entry;
    uint32_t self;
    uint32_t text;
    uint32_t line;
} Box;

static uint32_t style_of(const Box *b)
{
    return (uint32_t)(int32_t)(int8_t)port_u8(b->port, b->self, BOX_STYLE);
}

static uint32_t lines_of(const Box *b)
{
    return port_u8(b->port, b->self, BOX_LINES);
}

/* Copies line `index` into the line buffer (0x4eb860) and ends it. */
static void copy_line(const Box *b, uint32_t index)
{
    const uint32_t offset = port_u16(b->port, b->self + index * 2, BOX_LINE_OFFSETS);
    const uint32_t length = port_u16(b->port, b->self + index * 2, BOX_LINE_LENGTHS);
    port_call(b->port, COPY_PADDED, b->line, b->text + offset, length, b->self + index * 2);
    port_set8(b->port, b->line + port_u16(b->port, b->self + index * 2, BOX_LINE_LENGTHS), 0, 0);
}

/* 0x4408e0 on the line buffer (stdcall, seven arguments) with its four measures at the frame
 * places given; returns nothing the caller uses. */
static void measure(const Box *b, uint32_t edx, uint32_t ebx, uint32_t ecx, uint32_t first,
                    uint32_t width, uint32_t height, uint32_t third, uint32_t fourth)
{
    const uint32_t esp = b->entry->esp;
    const uint32_t pushed[7] = {first,       b->line,      port_u8(b->port, b->self, BOX_FONT),
                                esp - width, esp - height, esp - third,
                                esp - fourth};
    port_call_stack(b->port, MEASURE, style_of(b), edx, ebx, ecx, pushed, 7);
}

/* Original 0x4b2a00 (eax = the text box, edx = the surface): draws the box's lines. The text
 * (+0x15c) is copied line by line into a buffer of its length plus one (0x4ec160). With +0x304 and
 * +0x2fc both 1 the widest line is measured (0x4408e0, unsigned). With +0x300 1 the lines' heights
 * plus one are summed in a word and the text centred vertically (half the room left by the height
 * +0xf8 less the paddings, when positive). Lines start at the left plus the left padding; with
 * +0x2fc 1 and +0x304 1 they are centred on the widest (half the room, a logical shift, when
 * positive as a word), with +0x2fc 1 alone they end at the right less the right padding. Each line
 * is measured at its place, drawn (0x440a20 when centred, else 0x440ca0) and the next goes one
 * line height plus one lower. The buffer is freed (0x4ea190). Registers and the measures' frame
 * places are what the original hands; eax is 0x4ea190's result, no caller reads edx. */
uint32_t vertrix_port_text_box_draw_4b2a00(PORT_SIGNATURE)
{
    Port port;
    uint8_t stack[BELOW + 8];
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    Box b = {&port, entry, entry->eax, 0, 0};
    const uint32_t esp = entry->esp;
    const uint32_t surface = entry->edx;
    b.text = port_u32(&port, b.self, BOX_TEXT);
    uint32_t length = 0;
    while (port_u8(&port, b.text + length, 0) != 0 && !port.env.failed)
    {
        length++;
    }
    b.line = port_call(&port, CLEAR_ALLOCATE, length + 1, 1, entry->ebx, length);

    uint32_t widest = 0;
    if (port_u32(&port, b.self, ALIGN_CENTRE) == 1 && port_u32(&port, b.self, ALIGN_LEFT) == 1)
    {
        const uint32_t lines = lines_of(&b);
        for (uint32_t i = 0; i < lines && !port.env.failed; i++)
        {
            copy_line(&b, i);
            measure(&b, 0, 0, 0, 0, WIDTH_A, HEIGHT_A, OUT_A3, OUT_A4);
            const uint32_t width = port_u32(&port, esp - WIDTH_A, 0);
            if (width > widest)
            {
                widest = width;
            }
        }
    }

    uint16_t top;
    const int vertical = port_u32(&port, b.self, ALIGN_MIDDLE) == 1;
    if (vertical)
    {
        uint32_t total = 0;
        const uint32_t lines = lines_of(&b);
        for (uint32_t i = 0; i < lines && !port.env.failed; i++)
        {
            copy_line(&b, i);
            measure(&b, 0, 0, 0, 0, WIDTH_C, HEIGHT_C, OUT_C3, OUT_C4);
            total = (total + port_u32(&port, esp - HEIGHT_C, 0) + 1) & 0xffff;
        }
        int32_t room = (int32_t)(int16_t)port_u16(&port, b.self, BOX_HEIGHT) -
                       (int32_t)(int16_t)total - (int32_t)port_u16(&port, b.self, PAD_TOP) -
                       (int32_t)port_u16(&port, b.self, PAD_BOTTOM);
        const int32_t half = (room - (room >> 31)) >> 1;
        top = (uint16_t)(port_u16(&port, b.self, BOX_TOP) + port_u16(&port, b.self, PAD_TOP));
        if ((int16_t)half > 0)
        {
            top = (uint16_t)(top + half);
        }
    }
    else
    {
        top = (uint16_t)(port_u16(&port, b.self, BOX_TOP) + port_u16(&port, b.self, PAD_TOP));
    }

    uint16_t start =
        (uint16_t)(port_u16(&port, b.self, BOX_LEFT) + port_u16(&port, b.self, PAD_LEFT));
    uint16_t left = start;
    if (port_u32(&port, b.self, ALIGN_LEFT) == 1)
    {
        if (port_u32(&port, b.self, ALIGN_CENTRE) == 1)
        {
            const uint32_t room =
                (uint32_t)((int32_t)(int16_t)port_u16(&port, b.self, BOX_WIDTH) - (int32_t)widest -
                           (int32_t)port_u16(&port, b.self, PAD_LEFT) -
                           (int32_t)port_u16(&port, b.self, PAD_RIGHT));
            const uint16_t half = (uint16_t)(room >> 1);
            if ((int16_t)half > 0)
            {
                start = (uint16_t)(start + half);
            }
            left = start;
        }
        else
        {
            left =
                (uint16_t)(port_u16(&port, b.self, BOX_LEFT) + port_u16(&port, b.self, BOX_WIDTH) -
                           port_u16(&port, b.self, PAD_RIGHT) - 1);
        }
    }

    const uint32_t lines = lines_of(&b);
    for (uint32_t i = 0; i < lines && !port.env.failed; i++)
    {
        copy_line(&b, i);
        const uint32_t y = (uint32_t)(int32_t)(int16_t)top;
        const uint32_t x0 = (uint32_t)(int32_t)(int16_t)start;
        const uint32_t x = (uint32_t)(int32_t)(int16_t)left;
        measure(&b, x0, x, y, y, WIDTH_B, HEIGHT_B, OUT_B3, OUT_B4);
        if (port_u32(&port, b.self, ALIGN_CENTRE) == 1 && port_u32(&port, b.self, ALIGN_LEFT) == 1)
        {
            const uint32_t pushed[2] = {b.line, b.self};
            port_call_stack(&port, DRAW_GLYPHS, surface, style_of(&b), x0, y, pushed, 2);
        }
        else
        {
            const uint32_t pushed[4] = {y, y, b.line, b.self};
            port_call_stack(&port, DRAW, surface, style_of(&b), x0, x, pushed, 4);
        }
        top = (uint16_t)(top + port_u32(&port, esp - HEIGHT_B, 0) + 1);
    }
    const uint32_t result = port_call(&port, FREE, b.line, 0, 0, 0);
    return port_return(&port, result, 0);
}

enum
{
    /* 0x4b2d90's measure places: D for the widest line, E for the total height, F for the lines. */
    WIDTH_D = 0x78,
    HEIGHT_D = 0x74,
    OUT_D3 = 0x50,
    OUT_D4 = 0x48,
    WIDTH_E = 0x70,
    HEIGHT_E = 0x6c,
    OUT_E3 = 0x34,
    OUT_E4 = 0x4c,
    WIDTH_F = 0x64,
    HEIGHT_F = 0x60,
    OUT_F3 = 0x38,
    OUT_F4 = 0x44
};

/* Original 0x4b2d90 (eax = the text box): whether its lines fit its height. Lays them out as
 * 0x4b2a00 does (the widest line, the vertical centring, the alignment), measuring each line at its
 * place instead of drawing it; the total height is summed in edi, of which the word counts. Returns
 * 1 when the end of the last line less the top (+0x16, words, signed) is at most the dword +0xf8
 * (unsigned), else 0; no caller reads edx. */
uint32_t vertrix_port_text_box_fits_4b2d90(PORT_SIGNATURE)
{
    Port port;
    uint8_t stack[BELOW + 8];
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    Box b = {&port, entry, entry->eax, 0, 0};
    const uint32_t esp = entry->esp;
    b.text = port_u32(&port, b.self, BOX_TEXT);
    uint32_t length = 0;
    while (port_u8(&port, b.text + length, 0) != 0 && !port.env.failed)
    {
        length++;
    }
    b.line = port_call(&port, CLEAR_ALLOCATE, length + 1, 1, entry->ebx, length);

    uint32_t widest = 0;
    if (port_u32(&port, b.self, ALIGN_CENTRE) == 1 && port_u32(&port, b.self, ALIGN_LEFT) == 1)
    {
        const uint32_t lines = lines_of(&b);
        for (uint32_t i = 0; i < lines && !port.env.failed; i++)
        {
            copy_line(&b, i);
            measure(&b, 0, 0, 0, 0, WIDTH_D, HEIGHT_D, OUT_D3, OUT_D4);
            const uint32_t width = port_u32(&port, esp - WIDTH_D, 0);
            if (width > widest)
            {
                widest = width;
            }
        }
    }

    uint16_t y = (uint16_t)(port_u16(&port, b.self, BOX_TOP) + port_u16(&port, b.self, PAD_TOP));
    if (port_u32(&port, b.self, ALIGN_MIDDLE) == 1)
    {
        uint32_t total = 0;
        const uint32_t lines = lines_of(&b);
        for (uint32_t i = 0; i < lines && !port.env.failed; i++)
        {
            copy_line(&b, i);
            measure(&b, 0, 0, 0, 0, WIDTH_E, HEIGHT_E, OUT_E3, OUT_E4);
            total += port_u32(&port, esp - HEIGHT_E, 0) + 1;
        }
        const int32_t room = (int32_t)(int16_t)port_u16(&port, b.self, BOX_HEIGHT) -
                             (int32_t)(int16_t)total - (int32_t)port_u16(&port, b.self, PAD_TOP) -
                             (int32_t)port_u16(&port, b.self, PAD_BOTTOM);
        const int32_t half = (room - (room >> 31)) >> 1;
        if ((int16_t)half > 0)
        {
            y = (uint16_t)(y + half);
        }
    }

    uint16_t start =
        (uint16_t)(port_u16(&port, b.self, BOX_LEFT) + port_u16(&port, b.self, PAD_LEFT));
    uint16_t left = start;
    if (port_u32(&port, b.self, ALIGN_LEFT) == 1)
    {
        if (port_u32(&port, b.self, ALIGN_CENTRE) == 1)
        {
            const uint32_t room =
                (uint32_t)((int32_t)(int16_t)port_u16(&port, b.self, BOX_WIDTH) - (int32_t)widest -
                           (int32_t)port_u16(&port, b.self, PAD_LEFT) -
                           (int32_t)port_u16(&port, b.self, PAD_RIGHT));
            const uint16_t half = (uint16_t)(room >> 1);
            if ((int16_t)half > 0)
            {
                start = (uint16_t)(start + half);
            }
            left = start;
        }
        else
        {
            left =
                (uint16_t)(port_u16(&port, b.self, BOX_LEFT) + port_u16(&port, b.self, BOX_WIDTH) -
                           port_u16(&port, b.self, PAD_RIGHT) - 1);
        }
    }

    const uint32_t lines = lines_of(&b);
    for (uint32_t i = 0; i < lines && !port.env.failed; i++)
    {
        copy_line(&b, i);
        const uint32_t row = (uint32_t)(int32_t)(int16_t)y;
        measure(&b, (uint32_t)(int32_t)(int16_t)start, (uint32_t)(int32_t)(int16_t)left, row, row,
                WIDTH_F, HEIGHT_F, OUT_F3, OUT_F4);
        y = (uint16_t)(y + port_u32(&port, esp - HEIGHT_F, 0) + 1);
    }
    port_call(&port, FREE, b.line, 0, 0, 0);
    const uint32_t used =
        (uint32_t)((int32_t)(int16_t)y - (int32_t)(int16_t)port_u16(&port, b.self, BOX_TOP));
    return port_return(&port, used <= port_u32(&port, b.self, BOX_HEIGHT) ? 1 : 0, 0);
}
