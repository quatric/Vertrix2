#include "rtltzrules.h"

/* The runtime's TZ rule parser: a date as Jn (Julian day, no leap day), n (day of the year) or
 * Mm.w.d (day d of week w of month m), then an optional /h[:m[:s]] time (2:00 by default). */

enum
{
    /* The routine's frame under its return slot: the numbers 0x4e9670 parses into. */
    BELOW = 0x1c,
    NUMBER = 0xc,
    HOURS = 0x10,
    MINUTES = 0x14,
    SECONDS = 0x18,

    /* The rule: its time, then month, week, day and the day number, and its kind (1 Julian,
     * 0 month form, -1 day of the year). */
    RULE_SECONDS = 0,
    RULE_MINUTES = 4,
    RULE_HOURS = 8,
    RULE_WEEK = 0xc,
    RULE_MONTH = 0x10,
    RULE_WEEKDAY = 0x18,
    RULE_DAY = 0x1c,
    RULE_KIND = 0x20,
    KIND_JULIAN = 1,
    KIND_MONTH = 0,
    KIND_DAY = 0xffffffffu,
    DEFAULT_HOURS = 2,

    PARSE_NUMBER = 0x4e9670
};

/* Parses a number at text into the local `to`; returns the text after it. */
static uint32_t parse(Port *port, uint32_t text, uint32_t to)
{
    return port_call(port, PARSE_NUMBER, text, to, 0, 0);
}

/* Original 0x4e97b4 (eax = the text, edx = the rule): returns the text after the rule. */
uint32_t vertrix_port_rtl_tz_rule_parse_4e97b4(PORT_SIGNATURE)
{
    uint8_t stack[BELOW + 8];
    Port port;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    const uint32_t frame = entry->esp - 4;
    const uint32_t number = frame - NUMBER;
    const uint32_t hours = frame - HOURS;
    const uint32_t minutes = frame - MINUTES;
    const uint32_t seconds = frame - SECONDS;
    const uint32_t rule = entry->edx;
    uint32_t text = entry->eax;

    uint32_t kind = KIND_DAY;
    if (port_u8(&port, text, 0) == 'J')
    {
        kind = KIND_JULIAN;
        text++;
    }
    if (port_u8(&port, text, 0) == 'M')
    {
        kind = KIND_MONTH;
        text++;
    }
    port_set32(&port, rule, RULE_KIND, kind);
    text = parse(&port, text, number);
    if (kind != KIND_MONTH)
    {
        port_set32(&port, rule, RULE_DAY, port_u32(&port, number, 0));
    }
    else
    {
        port_set32(&port, rule, RULE_MONTH, port_u32(&port, number, 0) - 1);
        if (port_u8(&port, text, 0) == '.')
        {
            text = parse(&port, text + 1, number);
            port_set32(&port, rule, RULE_WEEK, port_u32(&port, number, 0));
            if (port_u8(&port, text, 0) == '.')
            {
                text = parse(&port, text + 1, number);
                port_set32(&port, rule, RULE_WEEKDAY, port_u32(&port, number, 0));
            }
        }
        port_set32(&port, rule, RULE_DAY, 0);
    }

    port_set32(&port, hours, 0, DEFAULT_HOURS);
    port_set32(&port, seconds, 0, 0);
    port_set32(&port, minutes, 0, 0);
    if (port_u8(&port, text, 0) == '/')
    {
        text = parse(&port, text + 1, hours);
        if (port_u8(&port, text, 0) == ':')
        {
            text = parse(&port, text + 1, minutes);
            if (port_u8(&port, text, 0) == ':')
            {
                text = parse(&port, text + 1, seconds);
            }
        }
    }
    port_set32(&port, rule, RULE_SECONDS, port_u32(&port, seconds, 0));
    port_set32(&port, rule, RULE_MINUTES, port_u32(&port, minutes, 0));
    port_set32(&port, rule, RULE_HOURS, port_u32(&port, hours, 0));
    return port_return(&port, text, 0);
}
