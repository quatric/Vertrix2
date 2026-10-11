#include "port_render_rule.h"

enum
{
    BLEND_KIND = 0x5bc00d,
    OPACITY = 0x5bc00e,
    BLEND_ON = 0x5bb739,
    MIRRORED = 0x5bb73a,
    OUTLINE = 0x5bc00c,
    CLIP = 0x5bc002,
    IMAGE_FORMAT = 0x5bc000,
    TARGET_FORMAT = 0x5bb730,
    HALF_OPACITY = 0x32,
    RULES = 0x4fed44,
    RULE_COUNT = 0x5c,
    TRAVERSE_FIRST = 0x5bbfff,
    TRAVERSE_DEPTH = 0x5bb738,
    TRAVERSE_LAST = 0x5bbff0
};

uint32_t vertrix_port_render_flags(PORT_SIGNATURE)
{
    Port port;
    uint32_t kind;
    uint32_t opacity;
    uint32_t flags = 0;
    uint32_t plain = 0;
    port_open(&port, calls, services, globals, entry);
    kind = port_u8(&port, 0, BLEND_KIND);
    opacity = port_u8(&port, 0, OPACITY);
    if (port_u8(&port, 0, MIRRORED) == 1)
    {
        flags = 0x80000;
    }
    if (entry->edx == 1)
    {
        plain = 1;
        flags += 0x100000;
    }
    else if (port_u8(&port, 0, BLEND_ON) == 0)
    {
        plain = 1;
        flags += 1;
    }
    else
    {
        flags += opacity == HALF_OPACITY ? 8 : 0x10;
        if (kind == 0)
        {
            flags += 0x100;
        }
        else if (kind <= 3)
        {
            flags += 0x200u << (kind - 1);
        }
        else if (kind <= 10)
        {
            flags += 0x1000u << (kind - 4);
            if (opacity != HALF_OPACITY)
            {
                flags -= 8;
            }
            plain = 1;
        }
    }
    if (port_u8(&port, 0, IMAGE_FORMAT) != port_u8(&port, 0, TARGET_FORMAT))
    {
        flags += 4;
        if (plain == 1)
        {
            plain = port_u8(&port, 0, OUTLINE);
            flags += plain == 0 ? 0x20 : plain == 1 ? 0x40 : plain == 2 ? 0x80 : 0;
        }
    }
    if (port_u16(&port, 0, CLIP) != 0)
    {
        flags += 2;
    }
    port_set8(&port, 0, OPACITY, opacity);
    port_set8(&port, 0, BLEND_KIND, kind);
    return port_return(&port, flags, plain);
}

uint32_t vertrix_port_render_rule(PORT_SIGNATURE)
{
    Port port;
    uint32_t flags = entry->edx;
    uint32_t required = 0;
    uint32_t rule;
    port_open(&port, calls, services, globals, entry);
    for (rule = 0; rule < RULE_COUNT; rule++)
    {
        uint32_t allowed;
        required = port_u32(&port, 0, RULES + 8 * rule);
        allowed = port_u32(&port, 0, RULES + 8 * rule + 4);
        if ((flags & required) == required && (flags & ~(allowed | required)) == 0)
        {
            break;
        }
    }
    return port_return(&port, rule, required);
}

uint32_t vertrix_port_render_traversal_flags(PORT_SIGNATURE)
{
    Port port;
    uint32_t flags;
    port_open(&port, calls, services, globals, entry);
    flags = (port_u8(&port, 0, TRAVERSE_FIRST) != 1) + 1;
    if (port_u8(&port, 0, TRAVERSE_DEPTH) != 0x10)
    {
        flags += 4;
    }
    if (port_u8(&port, 0, TRAVERSE_LAST) == 1)
    {
        flags += 8;
    }
    return port_return(&port, flags, entry->edx);
}

/* The index of `value` in `keys`, or the key count. */
static uint32_t key_index(uint32_t value, const uint32_t *keys, uint32_t count)
{
    uint32_t i;
    for (i = 0; i < count && keys[i] != value; i++)
    {
    }
    return i;
}

uint32_t vertrix_port_render_mirror_index(PORT_SIGNATURE)
{
    static const uint32_t KEYS[] = {0, 8, 4, 0xc};
    Port port;
    port_open(&port, calls, services, globals, entry);
    return port_return(&port, key_index(entry->edx, KEYS, 4), entry->edx);
}

uint32_t vertrix_port_render_direction_index(PORT_SIGNATURE)
{
    static const uint32_t KEYS[] = {2, 1, 6, 5, 0xa, 9, 0xe, 0xd};
    Port port;
    port_open(&port, calls, services, globals, entry);
    return port_return(&port, key_index(entry->edx, KEYS, 8), entry->edx);
}
