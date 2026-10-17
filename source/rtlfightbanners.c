#include "rtlfightbanners.h"

enum
{
    /* The frame below the return slot (PORT_FRAMES), and its locals the callees reach by address
     * (offsets from the original's ebp, entry->esp - 4): the 48 line strings, the line being laid
     * out, and its measured width and height. */
    BELOW = 0x12c,
    LINES = 0x128,
    LINE_SLOTS = 0x30,
    LINE = 0x3c,
    WIDTH = 0x38,
    HEIGHT = 0x34,

    STRING_TYPE = 0x513e60,
    STRING_TYPE_KIND = 0x4,
    EMPTY_TEXT = 0x50e60d,
    PREPARE_TEXT = 0x50e60e,
    MIDDLE_TEXT = 0x50e616,
    FIGHT_TEXT = 0x50e619,
    /* The character's lines: three variants per character (a dword count each, 12 bytes a
     * character), plus 8; the texts 0xe4 bytes apart, 0x4c bytes a variant, 4 a character. */
    LINE_COUNTS = 0x53fd38,
    LINE_TEXTS = 0x53d998,
    LINE_TEXT_STRIDE = 0xe4,
    VARIANTS = 3,
    EXTRA_LINES = 8,
    FINAL_LINES = 3,
    RANDOM = 0x598d30,

    /* Layout: centred on 640 pixels (+0x11), the first line at 0x1a4, lines 0x32 apart, letters
     * 0x23 apart; the measure's text height 0x10. */
    FONT = 0x4f9c0a,
    SCREEN_WIDTH = 0x280,
    LEFT = 0x11,
    FIRST_Y = 0x1a4,
    LINE_STEP = 0x32,
    LETTER_STEP = 0x23,
    MEASURE_HEIGHT = 0x10,
    STRING_LENGTH = 8,

    /* The letter actors. */
    ACTOR_BYTES = 0x15c,
    ACTOR_X = 0x8,
    ACTOR_Y = 0xa,
    ACTOR_Z = 0xc,
    ACTOR_X1 = 0xe,
    ACTOR_X2 = 0x10,
    ACTOR_FLAG_A = 0x12,
    ACTOR_Y1 = 0x16,
    ACTOR_TARGET_Y = 0x18,
    ACTOR_FLAG_B = 0x1a,
    ACTOR_FLAG_C = 0x44,
    ACTOR_SPEED = 0x4e,
    ACTOR_MODE = 0x52,
    ACTOR_STAGE_A = 0x93,
    ACTOR_STAGE_B = 0x94,
    ACTOR_STAGE_C = 0x95,
    START_Y = 0xffd8,
    DROP_TOP = 0x1e0,
    DROP_MARGIN = 0x28,
    DROP_GAP = 0x14,
    DELAY = 0x14,
    PAINT = 0x4578f0,
    DROP_UPDATE = 0x457e40,
    NEXT = 0x458410,
    OBJECTS = 0x54671c,

    STRING_INIT = 0x4ca070,
    ARRAY_INIT = 0x4ccf3b,
    RANDOM_BELOW = 0x4826c0,
    STRING_SET_TEXT = 0x4ca370,
    STRING_ASSIGN = 0x4ca310,
    STRING_UPPER = 0x4ca710,
    TEXT_MEASURE = 0x440610,
    GET_MEM = 0x4ca000,
    ACTOR_RESET = 0x4abd70,
    ACTOR_PLACE = 0x4adf20,
    FONT_GLYPH = 0x43f420,
    ACTOR_SET_IMAGE = 0x4ac950,
    ACTOR_LOOKUP_IMAGE = 0x4ac8a0,
    ACTOR_SET_UPDATE = 0x4ac8f0,
    ACTOR_SET_NEXT = 0x4ac910,
    ACTOR_SET_DELAY = 0x4ac7d0,
    LIST_APPEND = 0x4b5e70,
    ARRAY_FINALIZE = 0x4cda10
};

static uint32_t font(Port *port)
{
    return (uint32_t)((int32_t)port_u32(port, FONT, 0) >> 24);
}

/* One letter actor of a line at x, y: placed with the paint routine, given the letter's glyph,
 * and (for the three final lines, `drop` their index among them) dropped in from above to a row
 * worked out from the text height, then linked and appended to the object list. */
static void spawn_letter(Port *port, uint32_t letter, uint32_t index, uint32_t count, uint32_t x,
                         uint32_t y, int final_line, uint32_t drop, uint32_t height)
{
    uint32_t actor = port_call(port, GET_MEM, ACTOR_BYTES, 0, 0, 0);
    if (actor != 0)
    {
        actor = port_call(port, ACTOR_RESET, actor, 0, 0, 0);
    }
    const uint32_t place[5] = {0, 0, 0, PAINT, 0};
    port_call_stack(port, ACTOR_PLACE, actor, 0, 0, 0, place, 5);
    const uint32_t glyph = port_call(port, FONT_GLYPH, font(port), letter, 0, 0);
    port_call(port, ACTOR_SET_IMAGE, actor, glyph, 0, 0);
    port_call(port, ACTOR_LOOKUP_IMAGE, actor, 0, 0, 0);
    port_set16(port, actor, ACTOR_Z, 0);
    port_set16(port, actor, ACTOR_X, x);
    port_set16(port, actor, ACTOR_Y, y);
    port_set16(port, actor, ACTOR_X1, x);
    port_set16(port, actor, ACTOR_Y1, y);
    port_set16(port, actor, ACTOR_X2, x);
    port_set16(port, actor, ACTOR_TARGET_Y, START_Y);
    if (final_line)
    {
        port_call(port, ACTOR_SET_UPDATE, actor, DROP_UPDATE, 0, 0);
        const uint32_t top = (DROP_TOP - (height * 3 + DROP_MARGIN)) >> 1;
        const uint32_t target = top + (height + DROP_GAP) * drop + (height >> 1);
        port_set8(port, actor, ACTOR_MODE, 0x9);
        port_set8(port, actor, ACTOR_STAGE_B, 0x1);
        port_set8(port, actor, ACTOR_STAGE_C, 0x4);
        port_set8(port, actor, ACTOR_STAGE_A, 0x1);
        port_set8(port, actor, ACTOR_SPEED, 0x32);
        port_set16(port, actor, ACTOR_TARGET_Y, target);
    }
    port_call(port, ACTOR_SET_NEXT, actor, NEXT, 0, index);
    port_set16(port, actor, ACTOR_FLAG_A, 1);
    port_set16(port, actor, ACTOR_FLAG_B, 1);
    port_set8(port, actor, ACTOR_FLAG_C, 0);
    port_call(port, ACTOR_SET_DELAY, actor, DELAY, 0, 0);
    port_call(port, LIST_APPEND, OBJECTS, actor, count, index);
}

/* Original 0x46ea30 (eax = the character): the letters of the lines shown before a fight. Fills the
 * 48 line strings with the empty text, picks one of three variants (random_below(3) on 0x598d30)
 * and takes its line count plus 8. The leading count - 8 lines are the variant's texts, uppercased;
 * the three last are 'PREPARE', the text at 0x50e616 and 'FIGHT' (the lines between keep the empty
 * text). Each line is measured (0x440610) and centred on 640 pixels, the first at y 0x1a4 and each
 * 0x32 below the one before; each letter becomes an actor 0x23 to the right of the one before. The
 * letters of the three last lines also drop in (0x457e40) to rows worked out from the text height.
 * Then the line strings are finalized (0x4cda10 with the edx and ecx the loops leave). No caller
 * reads a result. The exception frame at fs:[0] is left out (docs/NATIVE-PORTS.md). */
uint32_t vertrix_port_spawn_prepare_fight_letters_46ea30(PORT_SIGNATURE)
{
    Port port;
    uint8_t stack[BELOW + 8];
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    const uint32_t frame = entry->esp - 4;
    port_set32(&port, frame, 0, entry->ebp);
    const uint32_t character = entry->eax;
    const uint32_t lines = frame - LINES;
    const uint32_t line = frame - LINE;

    port_call(&port, STRING_INIT, line, 0, 0, 0);
    port_call(&port, ARRAY_INIT, lines, LINE_SLOTS, STRING_TYPE, STRING_TYPE_KIND);
    const uint32_t variant = port_call(&port, RANDOM_BELOW, RANDOM, VARIANTS, 0, 0) & 0xffff;
    const uint32_t count =
        port_u32(&port, LINE_COUNTS + character * 12 + variant * 4, 0) + EXTRA_LINES;
    for (uint32_t slot = lines; slot != lines + LINE_SLOTS * 4 && !port.env.failed; slot += 4)
    {
        port_call(&port, STRING_SET_TEXT, slot, EMPTY_TEXT, 0, 0);
    }

    uint32_t text = LINE_TEXTS + character * 4 + variant * 0x4c;
    const uint32_t texts_end = lines + (count - EXTRA_LINES) * 4;
    for (uint32_t slot = lines; slot < texts_end && !port.env.failed; slot += 4)
    {
        port_call(&port, STRING_ASSIGN, slot, text, 0, 0);
        port_call(&port, STRING_UPPER, slot, 0, 0, 0);
        text += LINE_TEXT_STRIDE;
    }
    port_call(&port, STRING_SET_TEXT, lines + count * 4 - 0xc, PREPARE_TEXT, 0, 0);
    port_call(&port, STRING_SET_TEXT, lines + count * 4 - 0x8, MIDDLE_TEXT, 0, 0);
    port_call(&port, STRING_SET_TEXT, lines + count * 4 - 0x4, FIGHT_TEXT, 0, 0);
    uint32_t finalize_edx = vertrix_lift_edx;
    uint32_t finalize_ecx = count * 4 - 4;

    if (count != 0)
    {
        const uint32_t first_final = count - FINAL_LINES;
        uint32_t y = FIRST_Y;
        for (uint32_t index = 0; index < count && !port.env.failed; index++)
        {
            port_call(&port, STRING_ASSIGN, line, port_u32(&port, lines + index * 4, 0), 0, 0);
            const uint32_t string = port_u32(&port, line, 0);
            const uint32_t length = port_u32(&port, string - STRING_LENGTH, 0);
            const uint32_t height_at = frame - HEIGHT;
            port_call_stack(&port, TEXT_MEASURE, font(&port), string, MEASURE_HEIGHT, frame - WIDTH,
                            &height_at, 1);
            uint32_t x = ((SCREEN_WIDTH - port_u32(&port, frame - WIDTH, 0) + 1) >> 1) + LEFT;
            for (uint32_t letter = 0; letter < length && !port.env.failed; letter++)
            {
                spawn_letter(&port, port_u8(&port, string + letter, 0), letter, length, x, y,
                             index >= first_final, index - first_final,
                             port_u32(&port, frame - HEIGHT, 0));
                x += LETTER_STEP;
            }
            y += LINE_STEP;
        }
        finalize_edx = lines + count * 4;
        finalize_ecx = FINAL_LINES;
    }
    port_call(&port, ARRAY_FINALIZE, 0, finalize_edx, 0, finalize_ecx);
    return port_return(&port, 0, 0);
}
