#include "rtlprintfs.h"

enum
{
    /* The printf state, at the foot of the frame under the saved esi, edi, es and ebp; the output
     * procedure, the spec parser and the formatter read it. */
    BELOW = 0x80,
    STATE = 0x80,

    OUTPUT = 0,
    WIDTH = 4,
    COUNT = 0x10,
    LETTER = 0x15,
    PAD = 0x16,
    /* A word the driver sets to 100; neither the spec parser nor the formatter reads it. */
    HUNDRED = 0x1c,
    FLAGS = 0x1e,
    /* What the formatter lays out: prefix characters, zeros, the text, zeros, more text, zeros. */
    PREFIX = 0x20,
    LEADING_ZEROS = 0x24,
    TEXT_LENGTH = 0x28,
    MIDDLE_ZEROS = 0x2c,
    TAIL_LENGTH = 0x30,
    TRAILING_ZEROS = 0x34,
    BUFFER = 0x38,
    PARSE_ARGUMENTS = 0x60,
    FORMAT_ARGUMENTS = 0x64,
    FORMAT = 0x68,
    WIDE = 0x6c,

    HUNDRED_VALUE = 100,
    FLAG_LEFT = 8,
    FLAG_SHORT = 0x10,
    FLAG_LONG = 0x20,
    FLAG_NEAR = 0x40,
    FLAG_FAR = 0x80,

    PARSE_SPEC = 0x4df6c8,
    FORMAT_VALUE = 0x4dfb24,
    WIDE_TEXT = 0x4dfac0
};

typedef struct Printf
{
    Port port;
    uint32_t state;
    uint32_t output;
} Printf;

static void put(Printf *printf_, uint32_t byte)
{
    port_call(&printf_->port, printf_->output, printf_->state, byte, 0, 0);
}

/* `byte` put once for each unit of a count of the state, the count run down to 0. */
static void put_run(Printf *printf_, uint32_t field, uint32_t byte)
{
    Port *port = &printf_->port;
    while ((int32_t)port_u32(port, printf_->state, field) > 0 && !port->env.failed)
    {
        put(printf_, byte);
        port_set32(port, printf_->state, field, port_u32(port, printf_->state, field) - 1);
    }
}

/* Characters from `*text` while a count of the state lasts. */
static void put_text(Printf *printf_, uint32_t field, uint32_t *text)
{
    Port *port = &printf_->port;
    while ((int32_t)port_u32(port, printf_->state, field) > 0 && !port->env.failed)
    {
        put(printf_, port_u8(port, *text, 0));
        port_set32(port, printf_->state, field, port_u32(port, printf_->state, field) - 1);
        *text += 1;
    }
}

/* %n: the count so far through the next argument, a far pointer (8 bytes) or a near one. */
static void store_count(Printf *printf_, uint32_t arguments)
{
    Port *port = &printf_->port;
    const uint32_t flags = port_u8(port, printf_->state, FLAGS);
    const uint32_t step = (flags & FLAG_FAR) ? 8 : 4;
    const uint32_t next = port_u32(port, arguments, 0) + step;
    port_set32(port, arguments, 0, next);
    const uint32_t target = port_u32(port, next - step, 0);
    const uint32_t count = port_u32(port, printf_->state, COUNT);
    if ((flags & FLAG_LONG) == 0 && (flags & FLAG_SHORT) != 0)
    {
        port_set16(port, target, 0, count);
    }
    else
    {
        port_set32(port, target, 0, count);
    }
}

/* Original 0x4df320 (eax = the output's state, edx = the format, ebx = where the argument pointer
 * is, ecx = the output procedure): printf. Characters other than '%' go to the procedure (eax =
 * the printf state, edx = the character). A spec is parsed (0x4df6c8); %n stores the count (a word
 * for h, else a dword, through a far or near pointer); any other is formatted (0x4dfb24) and laid
 * out: the width's padding (spaces before, unless left aligned or padded with zeros), the prefix,
 * zeros, the text (a wide string through 0x4dfac0), zeros, the rest of the text, zeros, then the
 * padding after when left aligned. Returns the count of characters. */
uint32_t vertrix_port_rtl_printf_4df320(PORT_SIGNATURE)
{
    Printf printf_;
    Port *port = &printf_.port;
    uint8_t stack[BELOW + 8];
    port_open_stack(port, stack, calls, services, globals, entry, BELOW);
    const uint32_t state = entry->esp - STATE;
    const uint32_t arguments = entry->ebx;
    printf_.state = state;
    printf_.output = entry->ecx;
    port_set8(port, state, WIDE, 0);
    port_set32(port, state, OUTPUT, entry->eax);
    port_set16(port, state, FLAGS, 0);
    port_set16(port, state, HUNDRED, HUNDRED_VALUE);
    port_set32(port, state, COUNT, 0);
    port_set32(port, state, FORMAT, entry->edx);
    if (port_u8(port, entry->edx, 0) == 0)
    {
        return port_return(port, 0, entry->edx);
    }
    do
    {
        const uint32_t format = port_u32(port, state, FORMAT);
        const uint32_t byte = port_u8(port, format, 0);
        if (byte != '%')
        {
            port_set32(port, state, FORMAT, format + 1);
            put(&printf_, byte);
            continue;
        }
        port_set32(port, state, PARSE_ARGUMENTS, port_u32(port, arguments, 0));
        const uint32_t after =
            port_call(port, PARSE_SPEC, format + 1, state + PARSE_ARGUMENTS, state, 0) + 1;
        port_set32(port, arguments, 0, port_u32(port, state, PARSE_ARGUMENTS));
        const uint32_t letter = port_u8(port, after - 1, 0);
        port_set32(port, state, FORMAT, after);
        port_set8(port, state, LETTER, letter);
        if (letter == 0)
        {
            break;
        }
        if (letter == 'n')
        {
            store_count(&printf_, arguments);
            continue;
        }
        port_set32(port, state, FORMAT_ARGUMENTS, port_u32(port, arguments, 0));
        uint32_t text = port_call(port, FORMAT_VALUE, state + BUFFER, state + FORMAT_ARGUMENTS,
                                  state, state + WIDE);
        const uint32_t segment = vertrix_lift_edx;
        port_set32(port, arguments, 0, port_u32(port, state, FORMAT_ARGUMENTS));
        uint32_t laid_out = 0;
        for (uint32_t field = PREFIX; field <= TRAILING_ZEROS; field += 4)
        {
            laid_out += port_u32(port, state, field);
        }
        port_set32(port, state, WIDTH, port_u32(port, state, WIDTH) - laid_out);
        if ((port_u8(port, state, FLAGS) & FLAG_LEFT) == 0 && port_u8(port, state, PAD) == ' ')
        {
            put_run(&printf_, WIDTH, ' ');
        }
        uint32_t prefix = state + BUFFER;
        put_text(&printf_, PREFIX, &prefix);
        put_run(&printf_, LEADING_ZEROS, '0');
        if (letter == 'S' || (letter == 's' && (port_u8(port, state, FLAGS) & FLAG_LONG)))
        {
            port_call(port, WIDE_TEXT, text, segment, state, printf_.output);
        }
        else
        {
            put_text(&printf_, TEXT_LENGTH, &text);
        }
        put_run(&printf_, MIDDLE_ZEROS, '0');
        put_text(&printf_, TAIL_LENGTH, &text);
        put_run(&printf_, TRAILING_ZEROS, '0');
        if (port_u8(port, state, FLAGS) & FLAG_LEFT)
        {
            put_run(&printf_, WIDTH, ' ');
        }
    } while (port_u8(port, port_u32(port, state, FORMAT), 0) != 0 && !port->env.failed);
    return port_return(port, port_u32(port, state, COUNT), vertrix_lift_edx);
}
