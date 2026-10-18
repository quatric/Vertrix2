#include "rtlrenderweights.h"

enum
{
    /* Byte table: value * percent / 100 for 101 percents of 256 values. */
    PERCENT_BYTES = 0x558cf0,
    /* Word table: value * percent / 100 for 101 percents of 512 values. */
    PERCENT_WORDS = 0x55f1f8,
    PERCENTS = 101,
    /* Byte tables: value * level / 255 for 256 levels of 256 values, the second in reverse level
     * order. */
    LEVEL_BYTES = 0x578600,
    LEVEL_BYTES_REVERSED = 0x588600,
    LEVELS = 256
};

/* Original 0x480730: builds the blending tables (unsigned quotients). Keeps edx; eax is the last
 * quotient, 255. */
uint32_t vertrix_port_render_weights_build_480730(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    for (uint32_t percent = 0; percent < PERCENTS && !port.env.failed; percent++)
    {
        for (uint32_t value = 0; value < 0x100; value++)
        {
            port_set8(&port, PERCENT_BYTES + percent * 0x100, value, value * percent / 100);
        }
    }
    for (uint32_t percent = 0; percent < PERCENTS && !port.env.failed; percent++)
    {
        for (uint32_t value = 0; value < 0x200; value++)
        {
            port_set16(&port, PERCENT_WORDS + percent * 0x400, value * 2, value * percent / 100);
        }
    }
    for (uint32_t level = 0; level < LEVELS && !port.env.failed; level++)
    {
        for (uint32_t value = 0; value < 0x100; value++)
        {
            const uint32_t weight = value * level / 0xff;
            port_set8(&port, LEVEL_BYTES + level * 0x100, value, weight);
            port_set8(&port, LEVEL_BYTES_REVERSED + (0xff - level) * 0x100, value, weight);
        }
    }
    return port_return(&port, 0xff, entry->edx);
}
