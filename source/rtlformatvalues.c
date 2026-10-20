#include "rtlformatvalues.h"

enum
{
    /* Locals under the saved esi, edi, es and ebp: a 64-bit value (+0), a 32-bit one (+8) and a
     * character's multibyte bytes (+0xc). */
    BELOW = 0x20,
    LOCALS = 0x20,
    LOW = 0,
    HIGH = 4,
    VALUE = 8,
    MULTIBYTE = 0xc,

    /* The printf state (0x4df320's). */
    WIDTH = 4,
    PRECISION = 8,
    LETTER = 0x15,
    FLAGS = 0x1e,
    SIZE_FLAGS = 0x1f,
    PREFIX = 0x20,
    LEADING_ZEROS = 0x24,
    TEXT_LENGTH = 0x28,
    TRAILING_ZEROS = 0x34,

    FLAG_ALTERNATE = 1,
    FLAG_SPACE = 2,
    FLAG_PLUS = 4,
    FLAG_SHORT = 0x10,
    FLAG_LONG = 0x20,
    FLAG_NEAR = 0x40,
    FLAG_FAR = 0x80,
    SIZE_64 = 1,

    DATA_SELECTOR = 0x10,
    /* The multibyte code page in use, and its lead byte table. */
    MULTIBYTE_ACTIVE = 0x5c8950,
    LEAD_BYTES = 0x5c8961,

    FORMAT_FIXED_POINT = 0x4df978,
    TEXT_LENGTH_LIMIT = 0x4df884,
    WIDE_TEXT_LENGTH_LIMIT = 0x4df8a8,
    FORMAT_FLOAT = 0x4dfa74,
    ZERO_PAD = 0x4dfa7c,
    TEXT_64 = 0x4e63b0,
    TEXT_32 = 0x4e64a0,
    TEXT_UPPER = 0x4e012c,
    HEX_DIGITS = 0x4df914,
    WIDE_TO_MULTIBYTE = 0x4e62e0
};

typedef struct Value
{
    Port port;
    uint32_t buffer;
    uint32_t arguments;
    uint32_t state;
    uint32_t locals;
} Value;

/* The next argument: the pointer at `arguments` moved 4 on. */
static uint32_t next(Value *value)
{
    Port *port = &value->port;
    const uint32_t at = port_u32(port, value->arguments, 0) + 4;
    port_set32(port, value->arguments, 0, at);
    return port_u32(port, at - 4, 0);
}

static uint32_t state_u32(Value *value, uint32_t field)
{
    return port_u32(&value->port, value->state, field);
}

static void prefix(Value *value, uint32_t byte)
{
    const uint32_t count = state_u32(value, PREFIX);
    port_set32(&value->port, value->state, PREFIX, count + 1);
    port_set8(&value->port, value->buffer, count, byte);
}

static uint32_t call(Value *value, uint32_t target, uint32_t eax, uint32_t edx, uint32_t ebx)
{
    return port_call(&value->port, target, eax, edx, ebx, value->state);
}

static int is_unsigned(uint32_t letter)
{
    return letter == 'X' || letter == 'o' || letter == 'u' || letter == 'x';
}

static int is_integer(uint32_t letter)
{
    return is_unsigned(letter) || letter == 'd' || letter == 'i';
}

/* The integer argument to the locals; for d and i, its sign or the + or space flag to the prefix
 * and the magnitude kept. */
static void take_integer(Value *value, uint32_t letter)
{
    Port *port = &value->port;
    const uint32_t flags = port_u8(port, value->state, FLAGS);
    const int wide = port_u8(port, value->state, SIZE_FLAGS) & SIZE_64;
    if (wide)
    {
        port_set32(port, value->locals, LOW, next(value));
        port_set32(port, value->locals, HIGH, next(value));
    }
    else
    {
        uint32_t number = next(value);
        if (!(flags & FLAG_LONG) && (flags & FLAG_SHORT))
        {
            number = is_unsigned(letter) ? (number & 0xffff) : (uint32_t)(int32_t)(int16_t)number;
        }
        port_set32(port, value->locals, VALUE, number);
    }
    if (is_unsigned(letter))
    {
        return;
    }
    const int negative = wide ? (port_u32(port, value->locals, HIGH) & 0x80000000u) != 0
                              : (int32_t)port_u32(port, value->locals, VALUE) < 0;
    if (negative)
    {
        prefix(value, '-');
        if (wide)
        {
            const uint32_t low = ~port_u32(port, value->locals, LOW) + 1;
            const uint32_t high = ~port_u32(port, value->locals, HIGH) + (low == 0);
            port_set32(port, value->locals, LOW, low);
            port_set32(port, value->locals, HIGH, high);
        }
        else
        {
            port_set32(port, value->locals, VALUE, 0 - port_u32(port, value->locals, VALUE));
        }
    }
    else if (flags & FLAG_PLUS)
    {
        prefix(value, '+');
    }
    else if (flags & FLAG_SPACE)
    {
        prefix(value, ' ');
    }
}

/* The digits of d, i, u, o, x and X after the prefix (0 or 0x for #), the zeros the precision
 * asks for; no digits for a zero with precision 0. Returns the text. */
static uint32_t integer_text(Value *value, uint32_t letter)
{
    Port *port = &value->port;
    const int wide = port_u8(port, value->state, SIZE_FLAGS) & SIZE_64;
    const uint32_t flags = port_u8(port, value->state, FLAGS);
    uint32_t radix = 10;
    if (letter == 'x' || letter == 'X')
    {
        const int zero =
            wide ? (port_u32(port, value->locals, LOW) | port_u32(port, value->locals, HIGH)) == 0
                 : port_u32(port, value->locals, VALUE) == 0;
        if ((flags & FLAG_ALTERNATE) && !zero)
        {
            prefix(value, '0');
            prefix(value, letter);
        }
        radix = 16;
    }
    else if (letter == 'o')
    {
        radix = 8;
        if (flags & FLAG_ALTERNATE)
        {
            prefix(value, '0');
        }
    }
    const uint32_t text = value->buffer + state_u32(value, PREFIX);
    const uint32_t precision = state_u32(value, PRECISION);
    uint32_t length;
    if (precision == 0 &&
        (wide ? (port_u32(port, value->locals, LOW) | port_u32(port, value->locals, HIGH)) == 0
              : port_u32(port, value->locals, VALUE) == 0))
    {
        port_set8(port, text, 0, 0);
        length = 0;
    }
    else
    {
        if (wide)
        {
            call(value, TEXT_64, value->locals + LOW, text, radix);
        }
        else
        {
            call(value, TEXT_32, port_u32(port, value->locals, VALUE), text, radix);
        }
        if (letter == 'X')
        {
            port_call(port, TEXT_UPPER, value->buffer, vertrix_lift_edx, radix, value->state);
        }
        length = call(value, TEXT_LENGTH_LIMIT, text, DATA_SELECTOR, 0xffffffffu);
    }
    port_set32(port, value->state, TEXT_LENGTH, length);
    if ((int32_t)length < (int32_t)precision)
    {
        port_set32(port, value->state, LEADING_ZEROS, precision - length);
    }
    if (precision == 0xffffffffu)
    {
        port_call(port, ZERO_PAD, value->state, length, 0xffffffffu, value->state);
    }
    return text;
}

/* %s and %S: the string argument (far, near or flat; none is the empty buffer) and its length,
 * wide or narrow, cut to the precision. Returns the text, `*segment` its selector. */
static uint32_t string_text(Value *value, uint32_t letter, uint32_t *segment)
{
    Port *port = &value->port;
    const uint32_t flags = port_u8(port, value->state, FLAGS);
    uint32_t text = value->buffer;
    port_set8(port, value->buffer, 0, 0);
    if (flags & FLAG_FAR)
    {
        const uint32_t at = port_u32(port, value->arguments, 0) + 8;
        port_set32(port, value->arguments, 0, at);
        const uint32_t offset = port_u32(port, at - 8, 0);
        const uint32_t selector = port_u16(port, at - 4, 0);
        if (offset != 0 || selector != 0)
        {
            *segment = selector;
            text = offset;
        }
    }
    else
    {
        const uint32_t offset = next(value);
        if (offset != 0)
        {
            text = offset;
            *segment = DATA_SELECTOR;
        }
    }
    const int wide = letter == 'S' ? !(flags & FLAG_SHORT) : (flags & FLAG_LONG) != 0;
    const uint32_t precision = state_u32(value, PRECISION);
    uint32_t length =
        call(value, wide ? WIDE_TEXT_LENGTH_LIMIT : TEXT_LENGTH_LIMIT, text, *segment, precision);
    if ((int32_t)precision >= 0 && (int32_t)length > (int32_t)precision)
    {
        length = precision;
    }
    port_set32(port, value->state, TEXT_LENGTH, length);
    return text;
}

/* %p and %P: eight hex digits, or a far pointer's selector:offset, in a width of 8 or 13 unless
 * one was given; the + and space flags dropped. */
static void pointer_text(Value *value, uint32_t letter)
{
    Port *port = &value->port;
    if (state_u32(value, WIDTH) == 0)
    {
        port_set32(port, value->state, WIDTH,
                   (port_u8(port, value->state, FLAGS) & FLAG_FAR) ? 13 : 8);
    }
    const uint32_t flags = port_u8(port, value->state, FLAGS) & ~(FLAG_SPACE | FLAG_PLUS);
    port_set8(port, value->state, FLAGS, flags);
    const uint32_t offset = next(value);
    if (flags & FLAG_FAR)
    {
        call(value, HEX_DIGITS, next(value) & 0xffff, value->buffer, 4);
        port_set8(port, value->buffer, 4, ':');
        call(value, HEX_DIGITS, offset, value->buffer + 5, 8);
    }
    else
    {
        call(value, HEX_DIGITS, offset, value->buffer, 8);
    }
    if (letter == 'P')
    {
        port_call(port, TEXT_UPPER, value->buffer, vertrix_lift_edx, 8, value->state);
    }
    port_set32(port, value->state, PREFIX,
               call(value, TEXT_LENGTH_LIMIT, value->buffer, DATA_SELECTOR, 0xffffffffu));
}

/* %c: the byte, or (with l) the wide character's multibyte form, two bytes for a lead byte. */
static void character_text(Value *value)
{
    Port *port = &value->port;
    port_set32(port, value->state, PREFIX, 1);
    if (!(port_u8(port, value->state, FLAGS) & FLAG_LONG))
    {
        port_set8(port, value->buffer, 0, next(value));
        return;
    }
    const uint32_t at = port_u32(port, value->arguments, 0) + 4;
    port_set32(port, value->arguments, 0, at);
    const uint32_t wide = port_u16(port, at - 4, 0);
    if (port_call(port, WIDE_TO_MULTIBYTE, value->locals + MULTIBYTE, wide, at, value->state) ==
        0xffffffffu)
    {
        return;
    }
    const uint32_t lead = port_u8(port, value->locals, MULTIBYTE);
    port_set8(port, value->buffer, 0, lead);
    if (port_u32(port, MULTIBYTE_ACTIVE, 0) == 0 || !(port_u8(port, LEAD_BYTES + lead, 0) & 1))
    {
        return;
    }
    port_set8(port, value->buffer, 1, port_u8(port, value->locals, MULTIBYTE + 1));
    port_set32(port, value->state, PREFIX, 2);
}

/* Original 0x4dfb24 (eax = the buffer, edx = where the argument pointer is, ebx = the printf
 * state): one spec's value laid out for 0x4df320. The counts (+0x20 to +0x34) start at 0; the
 * prefix (sign, 0, 0x) goes to the buffer, the text to the buffer after it or is the argument's
 * string. Integers (64-bit with I64, a word with h), strings, pointers, characters; e, f and g go
 * to the float formatter (0x4dfa74) and their text starts after the buffer's first byte, %hf to
 * the fixed point one (0x4df978). Any other letter is itself. Returns the text, edx its selector.
 */
uint32_t vertrix_port_rtl_format_value_4dfb24(PORT_SIGNATURE)
{
    Value value;
    Port *port = &value.port;
    uint8_t stack[BELOW + 8];
    port_open_stack(port, stack, calls, services, globals, entry, BELOW);
    value.buffer = entry->eax;
    value.arguments = entry->edx;
    value.state = entry->ebx;
    value.locals = entry->esp - LOCALS;
    for (uint32_t field = PREFIX; field <= TRAILING_ZEROS; field += 4)
    {
        port_set32(port, value.state, field, 0);
    }
    const uint32_t letter = port_u8(port, value.state, LETTER);
    uint32_t text = value.buffer;
    uint32_t segment = DATA_SELECTOR;
    if (is_integer(letter))
    {
        take_integer(&value, letter);
        text = integer_text(&value, letter);
    }
    else if (letter == 's' || letter == 'S')
    {
        text = string_text(&value, letter, &segment);
    }
    else if (letter == 'p' || letter == 'P')
    {
        pointer_text(&value, letter);
    }
    else if (letter == 'c')
    {
        character_text(&value);
    }
    else if (letter == 'C')
    {
        const uint32_t wide = next(&value) & 0xffff;
        const uint32_t length =
            port_call(port, WIDE_TO_MULTIBYTE, value.buffer, wide, value.state, value.state);
        port_set32(port, value.state, PREFIX, length == 0xffffffffu ? 0 : length);
    }
    else if ((letter == 'f' || letter == 'F') && (port_u8(port, value.state, FLAGS) & FLAG_SHORT))
    {
        const uint32_t fixed = next(&value);
        port_set32(port, value.locals, VALUE, fixed);
        call(&value, FORMAT_FIXED_POINT, value.buffer, fixed, value.state);
        port_set32(port, value.state, TEXT_LENGTH,
                   call(&value, TEXT_LENGTH_LIMIT, value.buffer, DATA_SELECTOR, 0xffffffffu));
    }
    else if (letter == 'e' || letter == 'E' || letter == 'f' || letter == 'F' || letter == 'g' ||
             letter == 'G')
    {
        call(&value, FORMAT_FLOAT, value.buffer, value.arguments, value.state);
        port_call(port, ZERO_PAD, value.state, vertrix_lift_edx, value.state, value.state);
        text = value.buffer + 1;
    }
    else
    {
        port_set32(port, value.state, WIDTH, 0);
        port_set8(port, value.buffer, 0, letter);
        port_set32(port, value.state, PREFIX, 1);
    }
    return port_return(port, text, segment);
}
