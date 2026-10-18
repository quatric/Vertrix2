#include "rtlpalettecolours.h"

enum
{
    /* The stdcall arguments above the return slot: where green and blue go. */
    ARGUMENTS = 2,
    ARGUMENT_GREEN = 4,
    ARGUMENT_BLUE = 8,

    /* The working singles: red, green, blue, hue, saturation and value (0..1), the hue's
     * fraction, the value copied, the three blends (value * (1 - s * (1 - f)), value * (1 - s * f)
     * and value * (1 - s)), the hue's sector (16 bits) and the rounding fractions. */
    RED = 0x546870,
    GREEN = 0x546874,
    BLUE = 0x546878,
    HUE = 0x54687c,
    SATURATION = 0x546880,
    VALUE = 0x546884,
    FRACTION = 0x546888,
    VALUE_COPY = 0x54688c,
    RISING = 0x546890,
    FALLING = 0x546894,
    FLOOR = 0x546898,
    SECTOR = 0x54689c,
    RED_FRACTION = 0x5468a0,
    GREEN_FRACTION = 0x5468a4,
    BLUE_FRACTION = 0x5468a8,

    /* Constants: the doubles 0.01, 1/60, 255 and 0.5 (high, low words) and the singles 1 and
     * 360. */
    HUNDREDTH_LOW = 0x47ae147b,
    HUNDREDTH_HIGH = 0x3f847ae1,
    SIXTIETH_LOW = 0x11111111,
    SIXTIETH_HIGH = 0x3f911111,
    TWO_FIFTY_FIVE_HIGH = 0x406fe000,
    HALF_HIGH = 0x3fe00000,
    SINGLE_ONE = 0x3f800000,
    SINGLE_360 = 0x43b40000,
    COMPONENT_MASK = 0xffff,

    INTEGER_TO_DOUBLE = 0x4d6775,
    DOUBLE_MULTIPLY = 0x4db507,
    DOUBLE_TO_SINGLE = 0x4eb606,
    SINGLE_SUBTRACT = 0x4d809c,
    SINGLE_MULTIPLY = 0x4d8177,
    SINGLE_TO_DOUBLE = 0x4eb526,
    SINGLE_TO_UNSIGNED = 0x4d67b2,
    UNSIGNED_TO_SINGLE = 0x4d74a6,
    DOUBLE_COMPARE = 0x4eb57c
};

/* The registers as the original holds them; a call takes them all (some helpers read esi, edi
 * and ebp) and leaves its eax and edx. */
typedef struct
{
    Port *port;
    uint32_t eax;
    uint32_t edx;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t esi;
    uint32_t edi;
    uint32_t ebp;
} Registers;

static void call(Registers *r, uint32_t target)
{
    r->eax =
        port_call_with(r->port, target, r->eax, r->edx, r->ebx, r->ecx, r->esi, r->edi, r->ebp);
    r->edx = vertrix_lift_edx;
}

static uint32_t global(Registers *r, uint32_t address)
{
    return port_u32(r->port, address, 0);
}

static void set(Registers *r, uint32_t address, uint32_t value)
{
    port_set32(r->port, address, 0, value);
}

/* A percentage (the low word of value) as a single scaled by 0.01. */
static uint32_t percent(Registers *r, uint32_t value)
{
    r->eax = value & COMPONENT_MASK;
    r->ebx = HUNDREDTH_LOW;
    r->ecx = HUNDREDTH_HIGH;
    call(r, INTEGER_TO_DOUBLE);
    call(r, DOUBLE_MULTIPLY);
    call(r, DOUBLE_TO_SINGLE);
    return r->eax;
}

/* a * (1 - b) with the singles (0x4d809c, 0x4d8177). */
static uint32_t blend(Registers *r, uint32_t a, uint32_t b)
{
    r->edx = b;
    r->eax = SINGLE_ONE;
    call(r, SINGLE_SUBTRACT);
    r->edx = r->eax;
    r->eax = a;
    call(r, SINGLE_MULTIPLY);
    return r->eax;
}

/* The single at `component` scaled by 255. */
static void scale(Registers *r, uint32_t component)
{
    r->ecx = TWO_FIFTY_FIVE_HIGH;
    r->eax = global(r, component);
    r->ebx = 0;
    call(r, SINGLE_TO_DOUBLE);
    call(r, DOUBLE_MULTIPLY);
    call(r, DOUBLE_TO_SINGLE);
    set(r, component, r->eax);
}

/* The single at `component` rounded to the nearest whole number into a 16-bit output (0x4d67b2
 * truncates; one more when the fraction is at least 0.5), its fraction stored at `fraction`.
 * Leaves eax as the original does: the output pointer, or the rounded-up number. */
static void rounded(Registers *r, uint32_t component, uint32_t fraction, uint32_t output)
{
    r->eax = global(r, component);
    call(r, SINGLE_TO_UNSIGNED);
    r->esi = r->eax;
    r->eax = r->esi & COMPONENT_MASK;
    r->ecx = HALF_HIGH;
    call(r, UNSIGNED_TO_SINGLE);
    r->edx = r->eax;
    r->eax = global(r, component);
    r->ebx = 0;
    call(r, SINGLE_SUBTRACT);
    set(r, fraction, r->eax);
    call(r, SINGLE_TO_DOUBLE);
    call(r, DOUBLE_COMPARE);
    if ((vertrix_lift_fl.sf != 0) == (vertrix_lift_fl.of != 0))
    {
        r->eax = (r->esi & COMPONENT_MASK) + 1;
        port_set16(r->port, output, 0, r->eax);
    }
    else
    {
        r->eax = output;
        port_set16(r->port, output, 0, r->esi);
    }
}

/* Original 0x474910 (eax, edx, ebx = hue in degrees, saturation and value in percent, in their
 * low words, ecx = where red goes; stdcall: where green and blue go): the colour of a hue,
 * saturation and value as 0..255 components. Without saturation every component is the value;
 * else the hue (360 taken as 0) / 60 gives the sector (truncated) and its fraction f, and sectors
 * 0 to 5 take the value, value * (1 - s * (1 - f)), value * (1 - s * f) and value * (1 - s) in the
 * usual order (a later sector leaves the components as they were). Each is scaled by 255 and
 * rounded. eax is left as the original leaves it. */
uint32_t vertrix_port_rtl_palette_colour_474910(PORT_SIGNATURE)
{
    Port port;
    uint8_t stack[0xc + 8 + 4 * ARGUMENTS];
    port_open_arguments(&port, stack, calls, services, globals, entry, 0xc, ARGUMENTS);
    Registers r = {&port,      entry->eax & COMPONENT_MASK,
                   entry->edx, entry->ebx,
                   entry->ecx, entry->ebx,
                   entry->ecx, entry->ebp};
    call(&r, UNSIGNED_TO_SINGLE);
    set(&r, HUE, r.eax);
    set(&r, SATURATION, percent(&r, r.edx));
    const uint32_t value = percent(&r, r.esi);
    r.edx = global(&r, SATURATION);
    set(&r, VALUE, value);
    if (r.edx == 0)
    {
        set(&r, BLUE, value);
        set(&r, GREEN, value);
        set(&r, RED, value);
    }
    else
    {
        if (global(&r, HUE) == SINGLE_360)
        {
            r.ebx = 0;
            set(&r, HUE, 0);
        }
        r.ebx = SIXTIETH_LOW;
        r.eax = global(&r, HUE);
        r.ecx = SIXTIETH_HIGH;
        call(&r, SINGLE_TO_DOUBLE);
        call(&r, DOUBLE_MULTIPLY);
        call(&r, DOUBLE_TO_SINGLE);
        set(&r, HUE, r.eax);
        call(&r, SINGLE_TO_UNSIGNED);
        port_set16(&port, SECTOR, 0, r.eax);
        r.eax &= COMPONENT_MASK;
        call(&r, UNSIGNED_TO_SINGLE);
        r.edx = r.eax;
        r.eax = global(&r, HUE);
        call(&r, SINGLE_SUBTRACT);
        set(&r, FRACTION, r.eax);
        set(&r, VALUE_COPY, global(&r, VALUE));
        set(&r, FLOOR, blend(&r, global(&r, VALUE), global(&r, SATURATION)));
        r.edx = global(&r, FRACTION);
        r.eax = SINGLE_ONE;
        call(&r, SINGLE_SUBTRACT);
        r.edx = r.eax;
        r.eax = global(&r, SATURATION);
        call(&r, SINGLE_MULTIPLY);
        set(&r, RISING, blend(&r, global(&r, VALUE), r.eax));
        r.edx = global(&r, FRACTION);
        r.eax = global(&r, SATURATION);
        call(&r, SINGLE_MULTIPLY);
        const uint32_t falling = blend(&r, global(&r, VALUE), r.eax);
        /* The sector is loaded into dx (0x474a62), keeping edx's upper half. */
        const uint32_t sector = port_u16(&port, SECTOR, 0);
        r.edx = (r.edx & 0xffff0000u) | sector;
        set(&r, FALLING, falling);
        const uint32_t whole = global(&r, VALUE_COPY);
        const uint32_t floor = global(&r, FLOOR);
        switch (sector)
        {
            case 0:
                set(&r, RED, whole);
                set(&r, GREEN, global(&r, RISING));
                set(&r, BLUE, floor);
                break;
            case 1:
                r.edx = whole;
                set(&r, RED, falling);
                set(&r, GREEN, whole);
                set(&r, BLUE, floor);
                break;
            case 2:
                set(&r, GREEN, whole);
                set(&r, BLUE, global(&r, RISING));
                set(&r, RED, floor);
                break;
            case 3:
                r.edx = whole;
                set(&r, GREEN, falling);
                set(&r, BLUE, whole);
                set(&r, RED, floor);
                break;
            case 4:
                set(&r, BLUE, whole);
                set(&r, RED, global(&r, RISING));
                set(&r, GREEN, floor);
                break;
            case 5:
                r.edx = whole;
                set(&r, BLUE, falling);
                set(&r, RED, whole);
                set(&r, GREEN, floor);
                break;
            default:
                break;
        }
    }
    scale(&r, RED);
    scale(&r, GREEN);
    scale(&r, BLUE);
    rounded(&r, RED, RED_FRACTION, r.edi);
    rounded(&r, GREEN, GREEN_FRACTION, port_u32(&port, entry->esp, ARGUMENT_GREEN));
    rounded(&r, BLUE, BLUE_FRACTION, port_u32(&port, entry->esp, ARGUMENT_BLUE));
    return port_return(&port, r.eax, r.edx);
}
