#include "rtlpalettehues.h"

enum
{
    /* The stdcall arguments above the return slot: where the saturation and value go. */
    ARGUMENTS = 2,
    ARGUMENT_SATURATION = 4,
    ARGUMENT_VALUE = 8,

    /* The working singles: red, green and blue (0..1), hue, saturation, value (the largest),
     * smallest, largest, the spread, the rounded saturation and value, and the result (1 when the
     * colour has a hue). */
    RED = 0x546840,
    GREEN = 0x546844,
    BLUE = 0x546848,
    HUE = 0x54684c,
    SATURATION = 0x546850,
    VALUE = 0x546854,
    SMALLEST = 0x546858,
    LARGEST = 0x54685c,
    SPREAD = 0x546860,
    SATURATION_FRACTION = 0x546864,
    VALUE_FRACTION = 0x546868,
    HAS_HUE = 0x54686c,

    /* Double constants (high, low words): 1/255, 60, 100, 0.5, 120 and 240; single 360. */
    INVERSE_255_LOW = 0x10101010,
    INVERSE_255_HIGH = 0x3f701010,
    SIXTY_HIGH = 0x404e0000,
    HUNDRED_HIGH = 0x40590000,
    HALF_HIGH = 0x3fe00000,
    HUNDRED_TWENTY_HIGH = 0x405e0000,
    TWO_HUNDRED_FORTY_HIGH = 0x406e0000,
    SINGLE_360 = 0x43b40000,
    COMPONENT_MASK = 0xffff,

    INTEGER_TO_DOUBLE = 0x4d6775,
    DOUBLE_MULTIPLY = 0x4db507,
    DOUBLE_TO_SINGLE = 0x4eb606,
    SINGLE_COMPARE = 0x4d8082,
    SINGLE_SUBTRACT = 0x4d809c,
    SINGLE_DIVIDE = 0x4d81fe,
    SINGLE_ADD = 0x4d80a6,
    SINGLE_TO_DOUBLE = 0x4eb526,
    DOUBLE_DIVIDE = 0x4eb652,
    DOUBLE_ADD = 0x4db350,
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

/* The flags a compare helper leaves: less or equal, greater or equal. */
static int less_or_equal(void)
{
    return vertrix_lift_fl.zf != 0 || (vertrix_lift_fl.sf != 0) != (vertrix_lift_fl.of != 0);
}

static int greater_or_equal(void)
{
    return (vertrix_lift_fl.sf != 0) == (vertrix_lift_fl.of != 0);
}

/* A component (eax's low word) as a single scaled by 1/255. */
static uint32_t component(Registers *r, uint32_t value)
{
    r->ebx = INVERSE_255_LOW;
    r->eax = value & COMPONENT_MASK;
    r->ecx = INVERSE_255_HIGH;
    call(r, INTEGER_TO_DOUBLE);
    call(r, DOUBLE_MULTIPLY);
    call(r, DOUBLE_TO_SINGLE);
    return r->eax;
}

/* (first - second) * 60 / spread as a double (the spread single in esi). The original moves the
 * registers one way for red and green (0x474881, 0x4748c0) and another for blue (0x474805). */
static void hue_part(Registers *r, uint32_t first, uint32_t second, int blue)
{
    r->eax = global(r, first);
    r->edx = global(r, second);
    r->ecx = SIXTY_HIGH;
    call(r, SINGLE_SUBTRACT);
    r->ebx = 0;
    call(r, SINGLE_TO_DOUBLE);
    call(r, DOUBLE_MULTIPLY);
    if (!blue)
    {
        r->ecx = r->eax;
        r->eax = r->esi;
        r->ebx = r->edx;
        call(r, SINGLE_TO_DOUBLE);
        r->esi = r->eax;
        r->edi = r->edx;
        r->eax = r->ecx;
        r->edx = r->ebx;
        r->ebx = r->esi;
        r->ecx = r->edi;
    }
    else
    {
        r->ebx = r->eax;
        r->eax = r->esi;
        r->edi = r->edx;
        call(r, SINGLE_TO_DOUBLE);
        r->esi = r->eax;
        r->ecx = r->edx;
        r->eax = r->ebx;
        r->edx = r->edi;
        r->ebx = r->esi;
    }
    call(r, DOUBLE_DIVIDE);
}

/* A single scaled by 100 (0x4eb526, 0x4db507, 0x4eb606). */
static uint32_t percent(Registers *r, uint32_t value)
{
    r->ecx = HUNDRED_HIGH;
    r->eax = value;
    r->ebx = 0;
    call(r, SINGLE_TO_DOUBLE);
    call(r, DOUBLE_MULTIPLY);
    call(r, DOUBLE_TO_SINGLE);
    return r->eax;
}

/* The single at `value` rounded to the nearest whole number into a 16-bit output (0x4d67b2
 * truncates; one more when the fraction is at least 0.5), its fraction stored at `fraction`. */
static void rounded(Registers *r, uint32_t value, uint32_t fraction, uint32_t output)
{
    r->eax = global(r, value);
    call(r, SINGLE_TO_UNSIGNED);
    r->esi = r->eax;
    r->eax = r->esi & COMPONENT_MASK;
    r->ecx = HALF_HIGH;
    call(r, UNSIGNED_TO_SINGLE);
    r->edx = r->eax;
    r->eax = global(r, value);
    r->ebx = 0;
    call(r, SINGLE_SUBTRACT);
    port_set32(r->port, fraction, 0, r->eax);
    call(r, SINGLE_TO_DOUBLE);
    call(r, DOUBLE_COMPARE);
    if (greater_or_equal())
    {
        r->eax = (r->esi & COMPONENT_MASK) + 1;
    }
    else
    {
        r->eax = r->esi;
    }
    port_set16(r->port, output, 0, r->eax);
}

/* Original 0x474560 (eax, edx, ebx = red, green and blue in their low words, ecx = where the hue
 * goes; stdcall: where the saturation and the value go): the colour's hue (degrees), saturation
 * and value (percent), as 16-bit numbers. The components are scaled to 0..1 as singles; the value
 * is the largest, the saturation (largest - smallest) / largest (0 for black); the hue (with a
 * saturation) is 60 times the difference of the other two over the spread, plus 120 when green is
 * largest or 240 when blue is, plus 360 when negative. Hue truncates; saturation and value round.
 * Returns 1 when the colour has a hue, else 0. */
uint32_t vertrix_port_rtl_palette_hue_474560(PORT_SIGNATURE)
{
    Port port;
    uint8_t stack[0x10 + 8 + 4 * ARGUMENTS];
    port_open_arguments(&port, stack, calls, services, globals, entry, 0x10, ARGUMENTS);
    Registers r = {&port,      entry->eax, entry->edx, entry->ebx,
                   entry->ecx, entry->ebx, entry->edx, entry->ecx};
    port_set32(&port, RED, 0, component(&r, entry->eax));
    port_set32(&port, GREEN, 0, component(&r, r.edi));
    const uint32_t blue = component(&r, r.esi);
    r.edx = global(&r, GREEN);
    port_set32(&port, BLUE, 0, blue);

    /* The largest and the smallest component. */
    r.eax = global(&r, RED);
    call(&r, SINGLE_COMPARE);
    r.esi = less_or_equal() ? global(&r, GREEN) : global(&r, RED);
    r.edx = global(&r, BLUE);
    r.eax = r.esi;
    call(&r, SINGLE_COMPARE);
    if (less_or_equal())
    {
        r.esi = global(&r, BLUE);
    }
    r.eax = global(&r, RED);
    r.edx = global(&r, GREEN);
    port_set32(&port, LARGEST, 0, r.esi);
    call(&r, SINGLE_COMPARE);
    r.esi = greater_or_equal() ? global(&r, GREEN) : global(&r, RED);
    r.edx = global(&r, BLUE);
    r.eax = r.esi;
    call(&r, SINGLE_COMPARE);
    r.edx = greater_or_equal() ? global(&r, BLUE) : r.esi;
    r.eax = global(&r, LARGEST);
    port_set32(&port, SMALLEST, 0, r.edx);
    port_set32(&port, VALUE, 0, r.eax);

    int has_hue = 0;
    if (r.eax == 0)
    {
        port_set32(&port, SATURATION, 0, r.eax);
    }
    else
    {
        call(&r, SINGLE_SUBTRACT);
        r.edx = global(&r, LARGEST);
        r.esi = r.eax;
        call(&r, SINGLE_DIVIDE);
        port_set32(&port, SATURATION, 0, r.eax);
        has_hue = r.eax != 0;
    }
    if (!has_hue)
    {
        r.edx = 0;
        port_set32(&port, HUE, 0, 0);
        port_set32(&port, HAS_HUE, 0, 0);
    }
    else
    {
        r.eax = 1;
        r.edx = global(&r, LARGEST);
        port_set32(&port, HAS_HUE, 0, r.eax);
        r.eax = global(&r, RED);
        port_set32(&port, SPREAD, 0, r.esi);
        call(&r, SINGLE_COMPARE);
        int found = 1;
        if (vertrix_lift_fl.zf != 0)
        {
            /* Red largest: (green - blue) * 60 / spread. */
            hue_part(&r, GREEN, BLUE, 0);
        }
        else
        {
            r.eax = global(&r, GREEN);
            r.edx = global(&r, LARGEST);
            call(&r, SINGLE_COMPARE);
            if (vertrix_lift_fl.zf != 0)
            {
                /* Green largest: (blue - red) * 60 / spread + 120. */
                hue_part(&r, BLUE, RED, 0);
                r.ecx = HUNDRED_TWENTY_HIGH;
                r.ebx = 0;
                call(&r, DOUBLE_ADD);
            }
            else
            {
                r.eax = global(&r, BLUE);
                r.edx = global(&r, LARGEST);
                call(&r, SINGLE_COMPARE);
                found = vertrix_lift_fl.zf != 0;
                if (found)
                {
                    /* Blue largest: (red - green) * 60 / spread + 240. */
                    hue_part(&r, RED, GREEN, 1);
                    r.ecx = TWO_HUNDRED_FORTY_HIGH;
                    r.ebx = 0;
                    call(&r, DOUBLE_ADD);
                }
            }
        }
        if (found)
        {
            call(&r, DOUBLE_TO_SINGLE);
            port_set32(&port, HUE, 0, r.eax);
        }
        r.eax = global(&r, HUE);
        call(&r, SINGLE_TO_DOUBLE);
        if ((int32_t)r.edx < 0)
        {
            r.edx = SINGLE_360;
            r.eax = global(&r, HUE);
            call(&r, SINGLE_ADD);
            port_set32(&port, HUE, 0, r.eax);
        }
    }
    port_set32(&port, SATURATION, 0, percent(&r, global(&r, SATURATION)));
    port_set32(&port, VALUE, 0, percent(&r, global(&r, VALUE)));
    r.eax = global(&r, HUE);
    call(&r, SINGLE_TO_UNSIGNED);
    port_set16(&port, r.ebp, 0, r.eax);
    rounded(&r, SATURATION, SATURATION_FRACTION, port_u32(&port, entry->esp, ARGUMENT_SATURATION));
    rounded(&r, VALUE, VALUE_FRACTION, port_u32(&port, entry->esp, ARGUMENT_VALUE));
    return port_return(&port, global(&r, HAS_HUE), r.edx);
}
