#include "rtlscreenwipes.h"

enum
{
    /* The frame under the return slot: ebp, five saved registers and 0x28 bytes of locals. From
     * ebp: the exception record (-0x3c: link, handler, class, state), the column object (-0x28),
     * the screen object (-0x24), the two steps (-0x20, -0x1c) and the column count (-0x18). */
    BELOW = 0x40,
    RECORD_LINK = 0x3c,
    RECORD_HANDLER = 0x38,
    RECORD_CLASS = 0x34,
    RECORD_STATE = 0x30,
    COLUMNS_OBJECT = 0x28,
    SCREEN = 0x24,
    FIRST_STEP = 0x20,
    SECOND_STEP = 0x1c,
    COUNT = 0x18,

    HANDLER = 0x4ec1ec,
    HANDLER_CLASS = 0x514210,

    /* The wipe's state: whether it started and the last column count (480 at the start). */
    STARTED = 0x5405fc,
    LAST_COUNT = 0x540600,
    LINES = 0x1e0,

    /* The surfaces and the source rows: the drawn object (its +4 the width), the first and second
     * sources (0x558c80: its +4 and +8 the full copy's size; 0x558c88). */
    SURFACE = 0x558c7c,
    SOURCE = 0x558c80,
    SOURCE_TWO = 0x558c88,
    SURFACE_WIDTH = 4,
    SOURCE_WIDTH = 4,
    SOURCE_HEIGHT = 8,
    LIST = 0x54676c,
    LIST_COUNT = 0x58,
    DEVICE = 0x5b9c50,
    DOUBLE_480_HIGH = 0x407e0000,
    SHOW_LINES = 9,

    STATE_START = 0x4b7cd0,
    STATE_ENTER = 0x4b7d10,
    SOUND_START = 0x472570,
    SCREEN_START = 0x41d640,
    SCREEN_LOCK = 0x41d670,
    INPUT_POLL = 0x472350,
    LIST_FIND = 0x4b5eb0,
    DEVICE_BEGIN = 0x486d00,
    BLIT = 0x47ce10,
    INTEGER_TO_DOUBLE = 0x4d6775,
    DOUBLE_DIVIDE = 0x4eb652,
    DOUBLE_TO_SINGLE = 0x4eb606,
    SINGLE_TO_UNSIGNED = 0x4d67b2,
    SINGLE_ADD = 0x4d80a6,
    SCREEN_UNLOCK = 0x41d6d0,
    DEVICE_END = 0x486da0,
    DEVICE_FLIP = 0x487020,
    DEVICE_PRESENT = 0x486ed0,
    SCREEN_DRAW = 0x41d660,
    SCREEN_UPDATE = 0x41de80,
    SCREEN_FINISH = 0x41ddf0,
    INPUT_DONE = 0x472360,
    INPUT_STOP = 0x472330,
    SCREEN_LEAVE = 0x41ac80,
    SCREEN_CLOSE = 0x418830
};

/* The registers as the original holds them; a call takes them all (0x4d80a6 reads esi, edi and
 * ebp) and leaves its eax and edx. */
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

static uint32_t local(Registers *r, uint32_t offset)
{
    return port_u32(r->port, r->ebp - offset, 0);
}

/* One line (ecx) copied from a source at a column (the single in esi) by 0x47ce10 (eax = the
 * surface, ebx = 0; stdcall: 0, the column, the surface's width and 1). The line's register (edi)
 * moves on after the column is taken (0x423a63, 0x423ae1). */
static void blit_line(Registers *r, uint32_t source, int line_set_first)
{
    r->eax = port_u32(r->port, SURFACE, 0);
    r->edx = port_u32(r->port, r->eax, SURFACE_WIDTH);
    const uint32_t width = r->edx;
    port_set32(r->port, r->ebp - COLUMNS_OBJECT, 0, r->eax);
    r->eax = r->esi;
    if (line_set_first)
    {
        r->ecx = r->edi;
    }
    call(r, SINGLE_TO_UNSIGNED);
    const uint32_t args[4] = {0, r->eax, width, 1};
    r->ecx = r->edi;
    r->ebx = 0;
    r->edx = port_u32(r->port, source, 0);
    r->eax = local(r, COLUMNS_OBJECT);
    r->edi++;
    r->eax = port_call_stack(r->port, BLIT, r->eax, r->edx, r->ebx, r->ecx, args, 4);
    r->edx = vertrix_lift_edx;
}

/* 480 / count as a single (0x4d6775, 0x4eb652, 0x4eb606). */
static uint32_t step(Registers *r, uint32_t count)
{
    r->eax = count;
    call(r, INTEGER_TO_DOUBLE);
    r->ebx = r->eax;
    r->ecx = r->edx;
    r->edx = DOUBLE_480_HIGH;
    r->eax = 0;
    r->esi = 0;
    call(r, DOUBLE_DIVIDE);
    call(r, DOUBLE_TO_SINGLE);
    return r->eax;
}

/* Original 0x423960 (eax = the screen): one frame of the screen wipe. The first frame starts it
 * (0x5405fc set, the count 480, 0x4b7cd0, 0x472570, 0x41d640). The screen is locked (0x41d670
 * with 9) and the column count taken from the list's found entry (+0x58, or 0). The whole source
 * is copied while the last count is 480; when the count changed, lines 0 to count - 1 are copied
 * from the first source and count to 479 from the second, each at a column stepping by 480 /
 * count (resp. 480 / (480 - count)) from 0. The screen is unlocked and presented, the count kept
 * and the screen drawn; when 0x472360 says the input is done the wipe stops (0x472330, 0x41ac80,
 * 0x418830, 0x5405fc cleared from its edx). Returns the caller's exception chain and edx; the
 * exception frame at fs:[0] is left out (docs/NATIVE-PORTS.md). */
uint32_t vertrix_port_rtl_screen_wipe_423960(PORT_SIGNATURE)
{
    Port port;
    uint8_t stack[BELOW + 8];
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    const uint32_t chain = port.env.chain;
    const uint32_t screen = entry->eax;
    Registers r = {&port, 0, HANDLER, 0, HANDLER_CLASS, entry->esi, entry->edi, entry->esp - 4};
    port_set32(&port, r.ebp - SCREEN, 0, screen);
    port_set32(&port, r.ebp - RECORD_LINK, 0, chain);
    port_set32(&port, r.ebp - RECORD_HANDLER, 0, HANDLER);
    port_set32(&port, r.ebp - RECORD_CLASS, 0, HANDLER_CLASS);
    port_set32(&port, r.ebp - RECORD_STATE, 0, 0);
    const uint32_t started = port_u8(&port, STARTED, 0);
    r.eax = ((r.ebp - RECORD_LINK) & 0xffff00ffu) | (started << 8);
    if (started == 0)
    {
        r.edx = (r.edx & 0xffffff00u) | 1;
        r.esi = LINES;
        port_set8(&port, STARTED, 0, 1);
        port_set32(&port, LAST_COUNT, 0, LINES);
        call(&r, STATE_START);
        call(&r, SOUND_START);
        r.eax = screen;
        call(&r, SCREEN_START);
    }
    call(&r, STATE_ENTER);
    r.eax = screen;
    r.edx = SHOW_LINES;
    call(&r, SCREEN_LOCK);
    call(&r, INPUT_POLL);
    r.eax = LIST;
    call(&r, LIST_FIND);
    if (r.eax != 0)
    {
        r.eax = port_u32(&port, r.eax, LIST_COUNT);
    }
    const uint32_t count = r.eax;
    port_set32(&port, r.ebp - COUNT, 0, count);
    r.eax = DEVICE;
    call(&r, DEVICE_BEGIN);
    if (port_u32(&port, LAST_COUNT, 0) == LINES)
    {
        r.edx = port_u32(&port, SOURCE, 0);
        const uint32_t args[4] = {0, 0, port_u32(&port, r.edx, SOURCE_WIDTH),
                                  port_u32(&port, r.edx, SOURCE_HEIGHT)};
        r.eax = port_u32(&port, SURFACE, 0);
        r.ecx = 0;
        r.ebx = 0;
        r.eax = port_call_stack(&port, BLIT, r.eax, r.edx, r.ebx, r.ecx, args, 4);
        r.edx = vertrix_lift_edx;
    }
    r.esi = count;
    if (count != port_u32(&port, LAST_COUNT, 0))
    {
        const uint32_t first_step = step(&r, count);
        port_set32(&port, r.ebp - FIRST_STEP, 0, first_step);
        r.edi = 0;
        for (uint32_t line = 0; line < count && !port.env.failed; line++)
        {
            blit_line(&r, SOURCE, 1);
            r.edx = first_step;
            r.eax = r.esi;
            r.ecx = count;
            call(&r, SINGLE_ADD);
            r.esi = r.eax;
        }
        const uint32_t second_count = LINES - count;
        r.edi = count;
        const uint32_t second_step = step(&r, second_count);
        port_set32(&port, r.ebp - SECOND_STEP, 0, second_step);
        while (r.edi < LINES && !port.env.failed)
        {
            blit_line(&r, SOURCE_TWO, 0);
            r.edx = second_step;
            r.eax = r.esi;
            call(&r, SINGLE_ADD);
            r.esi = r.eax;
        }
    }
    r.eax = screen;
    call(&r, SCREEN_UNLOCK);
    r.eax = DEVICE;
    call(&r, DEVICE_END);
    r.eax = DEVICE;
    call(&r, DEVICE_FLIP);
    r.eax = DEVICE;
    call(&r, DEVICE_PRESENT);
    port_set32(&port, LAST_COUNT, 0, count);
    r.eax = screen;
    call(&r, SCREEN_DRAW);
    r.eax = screen;
    call(&r, SCREEN_UPDATE);
    r.eax = screen;
    call(&r, SCREEN_FINISH);
    call(&r, INPUT_DONE);
    if (r.eax == 1)
    {
        call(&r, INPUT_STOP);
        r.eax = screen;
        call(&r, SCREEN_LEAVE);
        r.eax = screen;
        r.edx &= 0xffff00ffu;
        call(&r, SCREEN_CLOSE);
        port_set8(&port, STARTED, 0, r.edx >> 8);
    }
    return port_return(&port, chain, entry->edx);
}
