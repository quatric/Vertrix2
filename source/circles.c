#include "circles.h"

/* The circle drawn by points. */

static uint32_t sign16(uint32_t value)
{
    return (uint32_t)(int32_t)(int16_t)value;
}

/* The word globals of the circle: its x, y and step, and the two tests. */
enum
{
    CIRCLE_X = 0x558a64,
    CIRCLE_Y = 0x558a66,
    CIRCLE_STEP = 0x558a68,
    CIRCLE_BELOW = 0x558a6c,
    CIRCLE_ABOVE = 0x558a6e,
    CIRCLE_CENTRE_X = 0x558a70,
    CIRCLE_CENTRE_Y = 0x558a74
};

static uint32_t circle_word(Port *port, uint32_t address)
{
    return sign16(port_u16(port, 0, address));
}

/* Original 0x479e50: the circle of the radius bx in the colour edx on the surface eax, centred
 * on half its width +4 and height +8 (0x558a70, 0x558a74): from x 0, y the radius and the step
 * 2 less twice it, the four points (centre x plus and less x, centre y less and plus y) are
 * plotted (0x479df0) while y is above 0. A step below 0 tests twice the step and y less 1
 * (0x558a6c): not above 0, x steps (the step gains twice x plus 1); a step above 0 tests twice
 * the step less twice x less 1 (0x558a6e): above 0, y steps down (the step loses twice y less
 * 1); otherwise both step (the step gains twice x less twice y plus 2). All in words. Returns
 * the last y; edx the last plot's. */
uint32_t vertrix_port_circle_points_479e50(PORT_SIGNATURE)
{
    Port port;
    uint32_t surface = entry->eax;
    uint32_t colour = entry->edx;
    uint32_t x;
    uint32_t y;
    uint32_t step;
    uint32_t test;
    int both;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, 0, CIRCLE_CENTRE_X, port_u32(&port, surface, 4) >> 1);
    port_set16(&port, 0, CIRCLE_Y, entry->ebx);
    port_set32(&port, 0, CIRCLE_CENTRE_Y, port_u32(&port, surface, 8) >> 1);
    port_set16(&port, 0, CIRCLE_X, 0);
    step = 2 - entry->ebx * 2;
    for (;;)
    {
        port_set16(&port, 0, CIRCLE_STEP, step);
        port_call_with(&port, 0x479df0, surface, colour,
                       circle_word(&port, CIRCLE_X) + port_u32(&port, 0, CIRCLE_CENTRE_X),
                       port_u32(&port, 0, CIRCLE_CENTRE_Y) - circle_word(&port, CIRCLE_Y), surface,
                       colour, entry->ebp);
        port_call_with(&port, 0x479df0, surface, colour,
                       port_u32(&port, 0, CIRCLE_CENTRE_X) - circle_word(&port, CIRCLE_X),
                       port_u32(&port, 0, CIRCLE_CENTRE_Y) - circle_word(&port, CIRCLE_Y), surface,
                       colour, entry->ebp);
        port_call_with(&port, 0x479df0, surface, colour,
                       port_u32(&port, 0, CIRCLE_CENTRE_X) - circle_word(&port, CIRCLE_X),
                       circle_word(&port, CIRCLE_Y) + port_u32(&port, 0, CIRCLE_CENTRE_Y), surface,
                       colour, entry->ebp);
        port_call_with(&port, 0x479df0, surface, colour,
                       circle_word(&port, CIRCLE_X) + port_u32(&port, 0, CIRCLE_CENTRE_X),
                       circle_word(&port, CIRCLE_Y) + port_u32(&port, 0, CIRCLE_CENTRE_Y), surface,
                       colour, entry->ebp);
        y = circle_word(&port, CIRCLE_Y);
        if ((int32_t)y <= 0 || port.env.failed)
        {
            return port_return(&port, y, vertrix_lift_edx);
        }
        x = port_u16(&port, 0, CIRCLE_X);
        step = circle_word(&port, CIRCLE_STEP);
        both = 1;
        if ((int32_t)step < 0)
        {
            test = step * 2 + y * 2 - 1;
            port_set16(&port, 0, CIRCLE_BELOW, test);
            if ((int32_t)sign16(test) <= 0)
            {
                x = (x + 1) & 0xffff;
                port_set16(&port, 0, CIRCLE_X, x);
                step = x * 2 + step + 1;
                continue;
            }
        }
        else if (step != 0)
        {
            test = step * 2 - x * 2 - 1;
            port_set16(&port, 0, CIRCLE_ABOVE, test);
            both = (int32_t)sign16(test) <= 0;
        }
        if (both)
        {
            x = (x + 1) & 0xffff;
            port_set16(&port, 0, CIRCLE_X, x);
            y = (y - 1) & 0xffff;
            step = x * 2 + step - y * 2 + 2;
        }
        else
        {
            y = (y - 1) & 0xffff;
            step = step - y * 2 + 1;
        }
        port_set16(&port, 0, CIRCLE_Y, y);
    }
}
