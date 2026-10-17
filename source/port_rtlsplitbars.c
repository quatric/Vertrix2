#include "port_rtlsplitbars.h"

/* An options menu slider: a bar split into a filled part and the rest by its value. */

enum
{
    ACTOR_X = 0xe,
    ACTOR_Y = 0x16,
    ACTOR_PALETTE_OFFSET = 0x48,
    ACTOR_WIDTH = 0xf4,
    ACTOR_HEIGHT = 0xf8,
    /* An actor's method table, and its draw(actor, target) method. */
    ACTOR_METHODS = 0x158,
    METHOD_DRAW = 8,

    SLIDER_NO_ENDS = 0x160,
    SLIDER_LEFT_END = 0x170,
    SLIDER_RIGHT_END = 0x174,
    SLIDER_FILLED = 0x17c,
    SLIDER_REST = 0x180,
    SLIDER_MIN = 0x184,
    SLIDER_MAX = 0x188,
    SLIDER_VALUE = 0x18c,

    /* Place an actor and size it: x and y (words), width and height (stack). */
    SET_BOX = 0x4b54d0
};

/* Draw one actor of the slider: a method call, which leaves the slider's y in ebx and the
 * method table in ecx as the original does. Returns the method's eax. */
static uint32_t draw(Port *port, uint32_t actor, uint32_t target, uint32_t y)
{
    const uint32_t methods = port_u32(port, actor, ACTOR_METHODS);
    return port_call(port, port_u32(port, methods, METHOD_DRAW), actor, target, y, methods);
}

/* Original 0x4b3de0 (eax = slider, edx = target): lay the slider out and draw it. Both parts take
 * the slider's palette offset; the filled part is (value - min) * width / (max - min) wide
 * (unsigned 32-bit, and with max = min the product, as the lifted division leaves it), from the
 * slider's x, and the rest fills the width after it, both at the slider's y and height (words).
 * The two parts are drawn, then the two ends unless +0x160 is set. Returns what the last draw
 * returns, eax and edx (its callers read both). */
uint32_t vertrix_port_split_bar_draw_4b3de0(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t slider = entry->eax;
    const uint32_t target = entry->edx;
    const uint32_t filled = port_u32(&port, slider, SLIDER_FILLED);
    const uint32_t rest = port_u32(&port, slider, SLIDER_REST);
    const uint32_t palette = port_u16(&port, slider, ACTOR_PALETTE_OFFSET);
    port_set16(&port, filled, ACTOR_PALETTE_OFFSET, palette);
    port_set16(&port, rest, ACTOR_PALETTE_OFFSET, palette);

    const uint32_t min = port_u32(&port, slider, SLIDER_MIN);
    const uint32_t width = port_u32(&port, slider, ACTOR_WIDTH);
    const uint32_t range = port_u32(&port, slider, SLIDER_MAX) - min;
    const uint32_t product = (port_u32(&port, slider, SLIDER_VALUE) - min) * width;
    const uint32_t fill = range != 0 ? product / range : product;

    const uint32_t x = port_u16(&port, slider, ACTOR_X);
    const uint32_t y = (uint32_t)(int32_t)(int16_t)port_u16(&port, slider, ACTOR_Y);
    const uint32_t height = port_u32(&port, slider, ACTOR_HEIGHT) & 0xffff;
    port_call_stack(&port, SET_BOX, filled, (uint32_t)(int32_t)(int16_t)x, y, fill & 0xffff,
                    &height, 1);
    port_call_stack(&port, SET_BOX, rest, (uint32_t)(int32_t)(int16_t)(x + fill), y,
                    (width - fill) & 0xffff, &height, 1);

    draw(&port, filled, target, y);
    uint32_t result = draw(&port, rest, target, y);
    if (port_u32(&port, slider, SLIDER_NO_ENDS) == 0)
    {
        draw(&port, port_u32(&port, slider, SLIDER_LEFT_END), target, y);
        result = draw(&port, port_u32(&port, slider, SLIDER_RIGHT_END), target, y);
    }
    return port_return(&port, result, vertrix_lift_edx);
}
