#include "rtlformatspecs.h"

/* MFC's CString::FormatV: estimates the length of the formatted text from the format and its
 * arguments, makes the buffer that long and formats into it. */

enum
{
    /* The copy of the argument list handed to the formatter, at the original's esp. */
    BELOW = 0x20,
    ARGUMENTS_COPY = 0x20,

    /* Size modifiers or'd into the type: h and l. */
    SHORT = 0x10000,
    LONG = 0x20000,
    /* The least room an integer, a pointer and a floating-point item take. */
    INTEGER_ROOM = 0x20,
    DOUBLE_ROOM = 0x80,
    /* A %#: room for 0x. */
    PREFIX_ROOM = 2,

    CHAR_NEXT = 0x4e1054,
    CHAR_LENGTH = 0x4e105a,
    ATOI = 0x4d6710,
    IS_DIGIT = 0x4e1060,
    WIDE_LENGTH = 0x4d8580,
    LSTRLEN = 0x4f1d24,
    GET_BUFFER = 0x4ca670,
    VSPRINTF = 0x4cd0a4,
    RELEASE_BUFFER = 0x4ca6c0
};

typedef struct
{
    Port *port;
    /* The va_list the caller passes by address: moved past each argument read. */
    uint32_t arguments;
    /* The original's ecx, which isdigit reads: the caller's at first, then the size modifier of
     * the last item, or the precision's start while it is read. */
    uint32_t ecx;
} Scan;

static uint32_t next(Scan *scan, uint32_t text)
{
    return port_call(scan->port, CHAR_NEXT, text, 0, 0, 0);
}

static uint32_t at(Scan *scan, uint32_t text)
{
    return port_u8(scan->port, text, 0);
}

/* va_arg: moves the list on by `size` and returns where the argument is. */
static uint32_t argument(Scan *scan, uint32_t size)
{
    port_set32(scan->port, scan->arguments, 0, port_u32(scan->port, scan->arguments, 0) + size);
    return port_u32(scan->port, scan->arguments, 0) - size;
}

/* atoi of the digits at `text`, then past them. Inside an item the original keeps 0 in edx
 * across its calls. */
static uint32_t number(Scan *scan, uint32_t *text, uint32_t start)
{
    const uint32_t value = port_call(scan->port, ATOI, *text, 0, *text, 0);
    if (at(scan, start) == 0)
    {
        return value;
    }
    while (!scan->port->env.failed &&
           port_call(scan->port, IS_DIGIT, (uint32_t)(int32_t)(int8_t)at(scan, *text), 0, 0,
                     scan->ecx) != 0)
    {
        *text = next(scan, *text);
        if (at(scan, *text) == 0)
        {
            break;
        }
    }
    return value;
}

static int32_t at_least_one(int32_t length)
{
    return length < 1 ? 1 : length;
}

/* Original 0x4cdbe0 (eax = the string, edx = the format, ebx = the address of the va_list). The
 * estimate: every character, and for each item its width, precision and room: a character 2, a
 * string its length (at least 1), integers and pointers 32, floating point 128 (an item's room
 * includes width plus precision; %E has none, as in MFC). The va_list is moved past every
 * argument; the formatter gets the list as it was. */
uint32_t vertrix_port_rtl_format_spec_4cdbe0(PORT_SIGNATURE)
{
    uint8_t stack[BELOW + 8];
    Port port;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    const uint32_t string = entry->eax;
    const uint32_t format = entry->edx;
    const uint32_t copy = entry->esp - ARGUMENTS_COPY;
    Scan scan = {&port, entry->ebx, entry->ecx};
    port_set32(&port, copy, 0, port_u32(&port, scan.arguments, 0));

    int32_t total = 0;
    uint32_t text = format;
    for (; at(&scan, text) != 0 && !port.env.failed; text = next(&scan, text))
    {
        if (at(&scan, text) != '%' || at(&scan, text = next(&scan, text)) == '%')
        {
            total += (int32_t)port_call(&port, CHAR_LENGTH, text, 0, 0, 0);
            continue;
        }

        /* Flags, and a width from the arguments. */
        int32_t width = 0;
        for (; at(&scan, text) != 0 && !port.env.failed; text = next(&scan, text))
        {
            const uint32_t flag = at(&scan, text);
            if (flag == '#')
            {
                total += PREFIX_ROOM;
            }
            else if (flag == '*')
            {
                width = (int32_t)port_u32(&port, argument(&scan, 4), 0);
            }
            else if (flag != '-' && flag != '+' && flag != '0' && flag != ' ')
            {
                break;
            }
        }
        if (width == 0)
        {
            width = (int32_t)number(&scan, &text, text);
        }

        int32_t precision = 0;
        if (at(&scan, text) == '.')
        {
            const uint32_t start = next(&scan, text);
            text = start;
            scan.ecx = start;
            if (at(&scan, start) == '*')
            {
                precision = (int32_t)port_u32(&port, argument(&scan, 4), 0);
                text = next(&scan, start);
            }
            else
            {
                precision = (int32_t)number(&scan, &text, start);
            }
        }

        uint32_t modifier = 0;
        switch (at(&scan, text))
        {
            case 'h':
                modifier = SHORT;
                text = next(&scan, text);
                break;
            case 'l':
                modifier = LONG;
                text = next(&scan, text);
                break;
            case 'F':
            case 'L':
            case 'N':
                text = next(&scan, text);
                break;
        }
        scan.ecx = modifier;

        int32_t item = 0;
        const uint32_t type = (uint32_t)(int32_t)(int8_t)at(&scan, text) | modifier;
        switch (type)
        {
            case 'c':
            case 'C':
            case 'c' | SHORT:
            case 'C' | SHORT:
            case 'c' | LONG:
            case 'C' | LONG:
                item = 2;
                argument(&scan, 4);
                break;
            case 's':
            case 's' | SHORT:
            case 'S' | SHORT:
            {
                const uint32_t pointer = port_u32(&port, argument(&scan, 4), 0);
                item = at_least_one(
                    (int32_t)port_call_stack(&port, LSTRLEN, 0, 0, 0, scan.ecx, &pointer, 1));
                break;
            }
            case 'S':
            case 's' | LONG:
            case 'S' | LONG:
                item = at_least_one((int32_t)port_call(
                    &port, WIDE_LENGTH, port_u32(&port, argument(&scan, 4), 0), 0, 0, scan.ecx));
                break;
        }

        if (item != 0)
        {
            if (item > width)
            {
                width = item;
            }
            total += precision != 0 && width >= precision ? precision : width;
            continue;
        }
        switch (at(&scan, text))
        {
            case 'd':
            case 'i':
            case 'u':
            case 'x':
            case 'X':
            case 'o':
                argument(&scan, 4);
                width += precision;
                total += width < INTEGER_ROOM ? INTEGER_ROOM : width;
                break;
            case 'e':
            case 'f':
            case 'g':
            case 'G':
                argument(&scan, 8);
                width += precision;
                total += width < DOUBLE_ROOM ? DOUBLE_ROOM : width;
                break;
            case 'p':
                argument(&scan, 4);
                width += precision;
                total += width < INTEGER_ROOM ? INTEGER_ROOM : width;
                break;
            case 'n':
                argument(&scan, 4);
                break;
        }
    }

    port_call(&port, GET_BUFFER, string, (uint32_t)total, 0, 0);
    port_call(&port, VSPRINTF, port_u32(&port, string, 0), format, copy, 0);
    const uint32_t result = port_call(&port, RELEASE_BUFFER, string, 0xffffffffu, 0, 0);
    /* va_end. */
    port_set32(&port, copy, 0, 0);
    return port_return(&port, result, 0);
}
