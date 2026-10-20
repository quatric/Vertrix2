#include "rtlcommandlines.h"

enum
{
    /* The command line past the program name, and the program name. */
    COMMAND_LINE = 0x5096ec,
    PROGRAM_NAME = 0x5096f0,
    /* Nonzero: a quote inside a quoted argument ends it and a backslash escapes a quote or a
     * backslash there; 0: quotes toggle, and only a backslash before a quote escapes it. */
    QUOTE_RULES = 0x5c8ab8,
    ARGUMENT_COUNT = 0x5c77f0,
    ARGUMENTS = 0x5c77f4,
    ARGUMENT_COUNT_COPY = 0x5c8ab0,
    ARGUMENTS_COPY = 0x5c8ab4,
    ARGUMENT_COUNT_SECOND = 0x5c77f8,
    ARGUMENTS_SECOND = 0x5c77fc,

    ALLOCATE = 0x4e7c90,

    /* 0x4e5f00's locals, under its saved ebx, ecx, edx, esi, edi and ebp: where the split left
     * the text (+0), the argument count with the program (+4) and the pointers' size (+8). */
    BELOW = 0x24,
    LOCALS = 0x24,
    TEXT_END = 0,
    COUNT = 4,
    POINTERS_SIZE = 8
};

static int blank(uint32_t byte)
{
    return byte == ' ' || byte == '\t';
}

/* The arguments of `text`: counted, and with `arguments` nonzero each one ended in place (quotes
 * and escapes taken out) and its start stored there. The end of the text goes to `end`. */
static uint32_t split(Port *port, uint32_t text, uint32_t arguments, uint32_t end)
{
    const uint32_t rules = port_u32(port, 0, QUOTE_RULES);
    uint32_t count = 0;
    for (;;)
    {
        while (blank(port_u8(port, text, 0)))
        {
            text++;
        }
        if (port_u8(port, text, 0) == 0 || port->env.failed)
        {
            break;
        }
        /* 1: in quotes from the start; 2: in quotes opened inside (toggling rules only). */
        uint32_t quoted = 0;
        if (port_u8(port, text, 0) == '"')
        {
            quoted = 1;
            text++;
        }
        const uint32_t start = text;
        uint32_t to = text;
        for (;;)
        {
            const uint32_t byte = port_u8(port, text, 0);
            if (byte == '"')
            {
                if (rules == 0)
                {
                    text++;
                    quoted = quoted == 0 ? 2 : 0;
                    continue;
                }
                if (quoted == 1)
                {
                    break;
                }
            }
            else if ((blank(byte) && quoted == 0) || byte == 0)
            {
                break;
            }
            else if (byte == '\\')
            {
                const uint32_t next = port_u8(port, text, 1);
                if (rules == 0)
                {
                    if (next == '"')
                    {
                        const uint32_t before = port_u8(port, text, -1u);
                        text++;
                        if (before == '\\')
                        {
                            continue;
                        }
                    }
                }
                else if (quoted == 1 ? next == '"' || next == '\\' : next == '"')
                {
                    text++;
                }
            }
            if (arguments != 0)
            {
                port_set8(port, to++, 0, port_u8(port, text, 0));
            }
            text++;
            if (port->env.failed)
            {
                break;
            }
        }
        if (arguments != 0)
        {
            port_set32(port, arguments, 4 * count, start);
        }
        count++;
        const uint32_t last = port_u8(port, text, 0);
        if (arguments != 0)
        {
            port_set8(port, to, 0, 0);
        }
        if (last == 0)
        {
            break;
        }
        text++;
    }
    port_set32(port, end, 0, text);
    port_set32(port, 0, QUOTE_RULES, rules);
    return count;
}

/* Original 0x4e5fe4 (eax = the text, edx = where the argument pointers go or 0, ebx = where the
 * end of the text goes): the command line's arguments, split at blanks outside quotes, counted,
 * and with edx stored (each ended in place, quotes and escapes taken out, under the quote rules of
 * 0x5c8ab8). Returns the count; edx is ebx. */
uint32_t vertrix_port_rtl_split_arguments_4e5fe4(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t count = split(&port, entry->eax, entry->edx, entry->ebx);
    return port_return(&port, count, entry->ebx);
}

/* Original 0x4e5f00: argc and argv. The command line (0x5096ec) is counted (0x4e5fe4's split, in
 * C here), copied into one block (0x4e7c90) with room for the pointers after it, and split again
 * there, the program name (0x5096f0) first and a null last; the count (with the program) and the
 * pointers go to 0x5c77f0/0x5c77f4 and their two copies. With no block, both are 0. Returns the
 * pointers; edx is kept. */
uint32_t vertrix_port_rtl_set_arguments_4e5f00(PORT_SIGNATURE)
{
    Port port;
    uint8_t stack[BELOW + 8];
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    const uint32_t locals = entry->esp - LOCALS;
    const uint32_t line = port_u32(&port, 0, COMMAND_LINE);
    const uint32_t count = split(&port, line, 0, locals + TEXT_END) + 1;
    port_set32(&port, locals, COUNT, count);
    const uint32_t length = port_u32(&port, locals, TEXT_END) - line;
    const uint32_t text_size = (length + 4) & ~3u;
    const uint32_t pointers_size = 4 * count;
    port_set32(&port, locals, POINTERS_SIZE, pointers_size);
    const uint32_t block = port_call(&port, ALLOCATE, (pointers_size + 4 + text_size + 3) & ~3u,
                                     text_size, locals, length + 1);
    uint32_t argc = 0;
    if (block == 0)
    {
        port_set32(&port, 0, ARGUMENTS, 0);
    }
    else
    {
        const uint32_t pointers = block + text_size;
        port_set32(&port, 0, ARGUMENTS, pointers);
        port_copy(&port, block, line, length + 1);
        port_set32(&port, pointers, 0, port_u32(&port, 0, PROGRAM_NAME));
        split(&port, block, pointers + 4, locals + TEXT_END);
        port_set32(&port, port_u32(&port, 0, ARGUMENTS), port_u32(&port, locals, POINTERS_SIZE), 0);
        argc = port_u32(&port, locals, COUNT);
    }
    const uint32_t argv = port_u32(&port, 0, ARGUMENTS);
    port_set32(&port, 0, ARGUMENT_COUNT, argc);
    port_set32(&port, 0, ARGUMENT_COUNT_COPY, argc);
    port_set32(&port, 0, ARGUMENTS_COPY, argv);
    port_set32(&port, 0, ARGUMENT_COUNT_SECOND, argc);
    port_set32(&port, 0, ARGUMENTS_SECOND, argv);
    return port_return(&port, argv, entry->edx);
}
