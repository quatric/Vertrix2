#include "rtltextwraps.h"

enum
{
    /* The frame below the return slot: the one-character and the space strings (AnsiString
     * locals whose addresses the string routines take) and the width and height 0x440610 measures
     * into, at the original's offsets from its ebp (entry->esp - 4). */
    BELOW = 0x6c,
    CHAR_STRING = 0x48,
    CHAR_WIDTH = 0x44,
    CHAR_HEIGHT = 0x40,
    SPACE_STRING = 0x3c,
    SPACE_WIDTH = 0x38,
    SPACE_HEIGHT = 0x34,

    /* Ten stack arguments: the left (word), the right and bottom (low words, sign-extended), the
     * two margins and two spacings (words) and three flags. */
    ARGUMENTS = 10,
    ARGUMENT_LEFT = 4,
    ARGUMENT_RIGHT = 8,
    ARGUMENT_BOTTOM = 0xc,
    ARGUMENT_MARGIN_LEFT = 0x10,
    ARGUMENT_MARGIN_RIGHT = 0x14,
    ARGUMENT_SPACING_A = 0x18,
    ARGUMENT_SPACING_B = 0x1c,
    ARGUMENT_FLAG_A = 0x20,
    ARGUMENT_FLAG_B = 0x24,
    ARGUMENT_FLAG_C = 0x28,

    /* The text object: the font word, the left, the right and bottom, the font spacing, the text
     * (an AnsiString), the font byte, the line count, and each line's start and length (words). */
    FIELD_FONT_WORD = 0xe,
    FIELD_LEFT = 0x16,
    FIELD_SPACING = 0x44,
    FIELD_RIGHT = 0xf4,
    FIELD_BOTTOM = 0xf8,
    FIELD_TEXT = 0x15c,
    FIELD_FONT = 0x160,
    FIELD_LINES = 0x161,
    FIELD_STARTS = 0x162,
    FIELD_LENGTHS = 0x22a,
    FIELD_MARGIN_LEFT = 0x2f2,
    FIELD_MARGIN_RIGHT = 0x2f4,
    FIELD_SPACING_A = 0x2f6,
    FIELD_SPACING_B = 0x2f8,
    FIELD_FLAG_A = 0x2fc,
    FIELD_FLAG_B = 0x300,
    FIELD_FLAG_C = 0x304,

    SPACE = 0x20,
    CHAR_LITERAL = 0x511083,
    SPACE_LITERAL = 0x511084,

    STRING_RELEASE = 0x4ca210,
    STRING_FROM_LITERAL = 0x4ca280,
    STRING_ASSIGN = 0x4ca370,
    STRING_APPEND = 0x4ca630,
    MEASURE = 0x440610
};

typedef struct
{
    Port *port;
    uint32_t frame;
    uint32_t object;
} Wrap;

static uint32_t sign16(uint32_t value)
{
    return ((value & 0xffff) ^ 0x8000u) - 0x8000u;
}

/* The width 0x440610 measures for the string at `string` (a frame local) in the object's font:
 * eax is the font byte sign-extended (read as the top of the dword at +0x15d), ebx the spacing at
 * +0x44, the width comes back at `width` and the height at `height`. */
static uint32_t measure(const Wrap *w, uint32_t string, uint32_t width, uint32_t height)
{
    const uint32_t height_at = w->frame - height;
    const uint32_t font = (uint32_t)((int32_t)port_u32(w->port, w->object, FIELD_FONT - 3) >> 24);
    port_call_stack(w->port, MEASURE, font, port_u32(w->port, w->frame - string, 0),
                    port_u8(w->port, w->object, FIELD_SPACING), w->frame - width, &height_at, 1);
    return port_u32(w->port, w->frame - width, 0);
}

/* The width of one character of the text as a string of its own. */
static uint32_t char_width(const Wrap *w, uint32_t at)
{
    const uint32_t string = w->frame - CHAR_STRING;
    port_call(w->port, STRING_FROM_LITERAL, string, CHAR_LITERAL, 0, 0);
    port_call(w->port, STRING_APPEND, string, port_u8(w->port, at, 0), 0, 0);
    const uint32_t width = measure(w, CHAR_STRING, CHAR_WIDTH, CHAR_HEIGHT);
    port_call(w->port, STRING_RELEASE, string, 0, 0, 0);
    return width;
}

static uint32_t space_width(const Wrap *w)
{
    const uint32_t string = w->frame - SPACE_STRING;
    port_call(w->port, STRING_FROM_LITERAL, string, SPACE_LITERAL, 0, 0);
    const uint32_t width = measure(w, SPACE_STRING, SPACE_WIDTH, SPACE_HEIGHT);
    port_call(w->port, STRING_RELEASE, string, 0, 0, 0);
    return width;
}

/* The object's copy of the text, read through the address of its string field each time. */
static uint32_t text_byte(const Wrap *w, uint32_t index)
{
    return port_u8(w->port, port_u32(w->port, w->object + FIELD_TEXT, 0) + index, 0);
}

static uint32_t line_count(const Wrap *w)
{
    return port_u8(w->port, w->object, FIELD_LINES);
}

/* Line `line`'s word at `field` (its start or its length), addressed from object + 2 * line. */
static uint32_t line_word(const Wrap *w, uint32_t line, uint32_t field)
{
    return port_u16(w->port, w->object + line * 2, field);
}

static void set_line_word(const Wrap *w, uint32_t line, uint32_t field, uint32_t value)
{
    port_set16(w->port, w->object + line * 2, field, value);
}

/* Close the current line at `position` and count it. */
static void close_line(const Wrap *w, uint32_t position)
{
    const uint32_t line = line_count(w);
    set_line_word(w, line, FIELD_LENGTHS, position - line_word(w, line, FIELD_STARTS));
    port_set8(w->port, w->object, FIELD_LINES, line_count(w) + 1);
}

/* Original 0x4b25b0 (eax = the text object, edx = the text, bl = the font byte, cx = the font word;
 * ten stack arguments, ret 0x28): breaks the text into lines. The text is assigned to the object's
 * string (+0x15c, 0x4ca370) and the arguments stored in the object. The width available is the
 * right argument less both margins. Leading spaces are skipped; then each word is measured one
 * character at a time (0x4ca280, 0x4ca630, 0x440610, 0x4ca210). A word that does not fit ends the
 * line and is measured again on the next one (forever, as in the original, when it fits on none);
 * the spaces after a word end the line when they overflow it. The last line is closed when it has
 * width, then each line's trailing spaces are trimmed from its length (a line whose characters
 * after the first are all spaces gets length 0). Words come from the text argument, spaces from the
 * object's copy. The line widths are 16-bit; the fs:[0] frame is left out and callers read neither
 * eax nor edx. */
uint32_t vertrix_port_text_wrap_4b25b0(PORT_SIGNATURE)
{
    uint8_t stack[BELOW + 8 + 4 * ARGUMENTS];
    Port port;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, ARGUMENTS);
    const Wrap w = {&port, entry->esp - 4, entry->eax};
    const uint32_t object = entry->eax;
    const uint32_t text = entry->edx;

    port_call(&port, STRING_ASSIGN, object + FIELD_TEXT, text, 0, 0);
    port_set8(&port, object, FIELD_FONT, entry->ebx);
    port_set16(&port, object, FIELD_FONT_WORD, entry->ecx);
    port_set16(&port, object, FIELD_LEFT, port_u32(&port, entry->esp, ARGUMENT_LEFT));
    const uint32_t right = port_u32(&port, entry->esp, ARGUMENT_RIGHT);
    port_set32(&port, object, FIELD_RIGHT, sign16(right));
    port_set32(&port, object, FIELD_BOTTOM, sign16(port_u32(&port, entry->esp, ARGUMENT_BOTTOM)));
    const uint32_t margin_left = port_u32(&port, entry->esp, ARGUMENT_MARGIN_LEFT);
    const uint32_t margin_right = port_u32(&port, entry->esp, ARGUMENT_MARGIN_RIGHT);
    port_set16(&port, object, FIELD_MARGIN_LEFT, margin_left);
    port_set16(&port, object, FIELD_MARGIN_RIGHT, margin_right);
    port_set16(&port, object, FIELD_SPACING_A, port_u32(&port, entry->esp, ARGUMENT_SPACING_A));
    port_set16(&port, object, FIELD_SPACING_B, port_u32(&port, entry->esp, ARGUMENT_SPACING_B));
    port_set32(&port, object, FIELD_FLAG_A, port_u32(&port, entry->esp, ARGUMENT_FLAG_A));
    port_set32(&port, object, FIELD_FLAG_B, port_u32(&port, entry->esp, ARGUMENT_FLAG_B));
    port_set32(&port, object, FIELD_FLAG_C, port_u32(&port, entry->esp, ARGUMENT_FLAG_C));

    uint32_t length = 0;
    while (port_u8(&port, text + length, 0) != 0 && !port.env.failed)
    {
        length++;
    }
    port_set8(&port, object, FIELD_LINES, 0);
    const int32_t available = (int32_t)((right - (margin_left + margin_right)) & 0xffff);

    /* Skip the leading spaces of the object's copy (its end compared as an address). */
    uint32_t position = 0;
    if (length != 0)
    {
        const uint32_t data = port_u32(&port, object + FIELD_TEXT, 0);
        for (uint32_t at = data; port_u8(&port, at, 0) == SPACE && !port.env.failed;)
        {
            position++;
            if (++at >= data + length)
            {
                break;
            }
        }
    }

    const uint32_t end = text + length;
    uint32_t running = 0;
    int new_line = 1;
    while (position < length && !port.env.failed)
    {
        /* Measure the word at `position`. */
        uint32_t scan = position;
        uint32_t word = 0;
        for (uint32_t at = text + position; port_u8(&port, at, 0) != SPACE && !port.env.failed;)
        {
            word = (word + char_width(&w, at)) & 0xffff;
            scan++;
            if (++at >= end)
            {
                break;
            }
        }
        if ((int32_t)(sign16(word) + running) > available)
        {
            close_line(&w, position);
            running = 0;
            new_line = 1;
            continue;
        }
        if (new_line)
        {
            set_line_word(&w, line_count(&w), FIELD_STARTS, position);
            new_line = 0;
        }
        running = (running + word) & 0xffff;
        position = scan;

        /* Then the spaces after it. */
        uint32_t spaces = 0;
        while (scan < length && text_byte(&w, scan) == SPACE && !port.env.failed)
        {
            spaces = (spaces + space_width(&w)) & 0xffff;
            scan++;
        }
        if ((int32_t)(running + sign16(spaces)) > available)
        {
            close_line(&w, position);
            running = 0;
            new_line = 1;
        }
        else
        {
            running = (running + spaces) & 0xffff;
        }
        position = scan;
    }
    if (running != 0)
    {
        close_line(&w, position);
    }

    /* Trim each line's trailing spaces. */
    for (uint32_t line = 0; line < line_count(&w) && !port.env.failed; line++)
    {
        int32_t last = (int32_t)line_word(&w, line, FIELD_LENGTHS) - 1;
        if (last <= 0)
        {
            continue;
        }
        while (last > 0 &&
               text_byte(&w, line_word(&w, line, FIELD_STARTS) + (uint32_t)last) == SPACE &&
               !port.env.failed)
        {
            last--;
        }
        set_line_word(&w, line, FIELD_LENGTHS, last > 0 ? (uint32_t)last + 1 : 0);
    }
    return port_return(&port, 0, 0);
}
