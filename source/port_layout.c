#include "port_layout.h"

enum
{
    SCREEN = 0x544070,
    SCREEN_WIDTH = 0x208,
    SCREEN_HEIGHT = 0x20c,
    SCREEN_SCALE_OFF = 0x220,
    SCREEN_SCALE = 0x221,
    SCREEN_SCALE_MAP = 0x270,
    SCALE_FULL = 0x10,
    SCALE_REMAINDERS = 0x5c1b00,
    ACTOR_X = 0x0e,
    ACTOR_Y = 0x16,
    ACTOR_DEPTH = 0x1e,
    ACTOR_SCALE = 0x44,
    ACTOR_SCREEN_SCALE = 0x91,
    ACTOR_IMAGE = 0xb4,
    ACTOR_ALIGN_X = 0xfc,
    ACTOR_ALIGN_Y = 0xfd,
    ACTOR_OFFSET_X = 0xfe,
    ACTOR_OFFSET_Y = 0x100,
    ACTOR_ANCHOR = 0x104,
    IMAGE_WIDTH = 0x04,
    IMAGE_HEIGHT = 0x08,
    IMAGE_ORIGIN_X = 0x0c,
    IMAGE_ORIGIN_Y = 0x10,
    /* The working globals (words unless noted). */
    L_ANCHOR = 0x5bb638, /* dword */
    L_ACTOR = 0x5bb63c,  /* dword */
    L_IMAGE = 0x5bb640,  /* dword */
    L_SCALE = 0x5bb644,  /* byte */
    L_INDEX = 0x5bb648,  /* dword */
    L_X = 0x5bb64c,
    L_Y = 0x5bb64e,
    L_SCREEN_WIDTH = 0x5bb650,
    L_SCREEN_HEIGHT = 0x5bb652,
    L_ANCHOR_X = 0x5bb654,
    L_SAVED_DI = 0x5bb656,
    L_ANCHOR_DEPTH = 0x5bb658,
    L_ORIGIN_X = 0x5bb65a,
    L_ORIGIN_Y = 0x5bb65c,
    L_SOURCE_WIDTH = 0x5bb65e,
    L_SOURCE_HEIGHT = 0x5bb660,
    L_DEPTH = 0x5bb662,
    L_SAVED_CX = 0x5bb664,
    L_SAVED_BX = 0x5bb666,
    L_ALIGN_X = 0x5bb668, /* byte */
    L_ALIGN_Y = 0x5bb669, /* byte */
    L_OFFSET_X = 0x5bb66a,
    L_OFFSET_Y = 0x5bb66c,
    L_LEFT = 0x5bb66e,
    L_TOP = 0x5bb670,
    L_RIGHT = 0x5bb672,
    L_BOTTOM = 0x5bb674,
    L_WIDTH = 0x5bb676,
    L_HEIGHT = 0x5bb678,
    L_SCALED_LEFT = 0x5bb67a,
    L_SCALED_TOP = 0x5bb67c,
    L_SCALED_RIGHT = 0x5bb67e,
    L_SCALED_BOTTOM = 0x5bb680,
    L_SCALED_WIDTH = 0x5bb682,
    L_SAVED_SI = 0x5bb684,
    L_SCALED_OFFSET_X = 0x5bb686,
    L_SCALED_OFFSET_Y = 0x5bb688
};

/* x86 partial register writes. */
static uint32_t set16(uint32_t reg, uint32_t value)
{
    return (reg & 0xffff0000u) | (value & 0xffff);
}

static uint32_t set8(uint32_t reg, uint32_t value)
{
    return (reg & 0xffffff00u) | (value & 0xff);
}

static uint32_t set8h(uint32_t reg, uint32_t value)
{
    return (reg & 0xffff00ffu) | ((value & 0xff) << 8);
}

/* The word at address + 2 sign-extended (the original's `mov r, [address]; sar r, 16`). */
static uint32_t high(Port *port, uint32_t address)
{
    return (uint32_t)((int32_t)port_u32(port, 0, address) >> 16);
}

/* Signed halving towards zero (`cdq; sub; sar 1`). */
static uint32_t half(uint32_t value)
{
    return (uint32_t)((int32_t)(value - (uint32_t)((int32_t)value >> 31)) >> 1);
}

/* `cdq; idiv divisor`: eax the quotient, unchanged when the division would fault. */
static uint32_t divide(uint32_t dividend, uint32_t divisor)
{
    uint32_t eax = dividend;
    uint32_t edx = (uint32_t)((int32_t)dividend >> 31);
    LiftFlags flags = {0, 0, 0, 0, 0, 0};
    lift_idiv1(32, divisor, &eax, &edx, &flags);
    return eax;
}

static uint32_t scaled(Port *port, uint32_t size, uint32_t scale)
{
    return port_u8(port, SCALE_REMAINDERS, scale * 16 + (size & 0xf));
}

uint32_t vertrix_port_actor_layout(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t anchor;
    uint32_t image;
    uint32_t screen;
    uint32_t eax = entry->eax;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t edx = entry->edx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t scale;
    port_open(&port, calls, services, globals, entry);
    ebx = set16(ebx, port_u16(&port, 0, L_SAVED_BX));
    ecx = set16(ecx, port_u16(&port, 0, L_SAVED_CX));
    esi = set16(esi, port_u16(&port, 0, L_SAVED_SI));
    edi = set16(edi, port_u16(&port, 0, L_SAVED_DI));
    anchor = port_u32(&port, actor, ACTOR_ANCHOR);
    port_set32(&port, 0, L_ACTOR, actor);
    if (anchor == 0)
    {
        goto done;
    }
    image = port_u32(&port, anchor, ACTOR_IMAGE);
    eax = anchor;
    port_set32(&port, 0, L_IMAGE, image);
    if (image == 0)
    {
        goto done;
    }
    /* The anchor's position, clamped to the screen. */
    port_set16(&port, 0, L_Y, port_u16(&port, anchor, ACTOR_Y));
    screen = port_u32(&port, 0, SCREEN);
    port_set16(&port, 0, L_X, port_u16(&port, anchor, ACTOR_X));
    edx = set16(image, port_u16(&port, screen, SCREEN_WIDTH));
    port_set16(&port, 0, L_SCREEN_HEIGHT, port_u16(&port, screen, SCREEN_HEIGHT));
    port_set16(&port, 0, L_SCREEN_WIDTH, edx);
    if ((int32_t)high(&port, 0x5bb64a) < 0)
    {
        ebx = 0;
        port_set16(&port, 0, L_X, 0);
    }
    else if ((int16_t)edx <= (int16_t)port_u16(&port, 0, L_X))
    {
        port_set16(&port, 0, L_X, edx - 1);
    }
    if ((int32_t)high(&port, L_X) < 0)
    {
        edi = 0;
        port_set16(&port, 0, L_Y, 0);
    }
    else
    {
        ecx = set16(ecx, port_u16(&port, 0, L_SCREEN_HEIGHT));
        if ((int16_t)port_u16(&port, 0, L_Y) >= (int16_t)ecx)
        {
            port_set16(&port, 0, L_Y, ecx - 1);
        }
    }
    edx = high(&port, L_Y) * high(&port, L_X) + high(&port, 0x5bb64a);
    port_set32(&port, 0, L_INDEX, edx);
    /* The scale in sixteenths. */
    if (port_u8(&port, anchor, ACTOR_SCREEN_SCALE) == 0)
    {
        scale = port_u8(&port, anchor, ACTOR_SCALE);
    }
    else
    {
        screen = port_u32(&port, 0, SCREEN);
        if (port_u8(&port, screen, SCREEN_SCALE_OFF) == 0)
        {
            scale = port_u8(&port, screen, SCREEN_SCALE);
        }
        else
        {
            ecx = port_u32(&port, 0, L_INDEX);
            scale = (port_u8(&port, port_u32(&port, port_u32(&port, screen, SCREEN_SCALE_MAP), 0),
                             ecx) +
                     1) &
                    0xff;
        }
    }
    port_set8(&port, 0, L_SCALE, scale);
    actor = port_u32(&port, 0, L_ACTOR);
    port_set8(&port, 0, L_ALIGN_X, port_u8(&port, actor, ACTOR_ALIGN_X));
    port_set8(&port, 0, L_ALIGN_Y, port_u8(&port, actor, ACTOR_ALIGN_Y));
    port_set16(&port, 0, L_OFFSET_X, port_u16(&port, actor, ACTOR_OFFSET_X));
    port_set16(&port, 0, L_OFFSET_Y, port_u16(&port, actor, ACTOR_OFFSET_Y));
    port_set16(&port, 0, L_ANCHOR_DEPTH, port_u16(&port, anchor, ACTOR_DEPTH));
    eax = port_u32(&port, 0, L_IMAGE);
    port_set16(&port, 0, L_ANCHOR_X, port_u16(&port, anchor, ACTOR_X));
    port_set16(&port, 0, L_ORIGIN_X, port_u16(&port, eax, IMAGE_ORIGIN_X));
    port_set16(&port, 0, L_ORIGIN_Y, port_u16(&port, eax, IMAGE_ORIGIN_Y));
    port_set16(&port, 0, L_WIDTH, port_u16(&port, eax, IMAGE_WIDTH));
    edx = set16(edx, port_u16(&port, eax, IMAGE_HEIGHT));
    ebx = set16(ebx, port_u16(&port, 0, L_ORIGIN_X));
    port_set16(&port, 0, L_HEIGHT, edx);
    /* The image's box around the anchor. */
    edx = set16(edx, port_u16(&port, 0, L_ANCHOR_X));
    edi = set16(edi, port_u16(&port, anchor, ACTOR_Y));
    edx -= ebx;
    ecx = set16(ecx, port_u16(&port, 0, L_ORIGIN_Y));
    port_set16(&port, 0, L_LEFT, edx);
    ebx = edi;
    edx = set16(edx, port_u16(&port, 0, L_ANCHOR_DEPTH));
    ebx -= ecx;
    ebx -= edx;
    edx = set16(edx, port_u16(&port, 0, L_LEFT));
    port_set16(&port, 0, L_TOP, ebx);
    edx = set16(edx, edx + port_u16(&port, 0, L_WIDTH));
    edx--;
    ecx = set16(ecx, port_u16(&port, 0, L_HEIGHT));
    port_set16(&port, 0, L_RIGHT, edx);
    edx = set16(edx, port_u16(&port, 0, L_TOP));
    edx += ecx;
    edx--;
    ebx = set8(ebx, port_u8(&port, 0, L_SCALE));
    port_set16(&port, 0, L_BOTTOM, edx);
    if ((ebx & 0xff) == SCALE_FULL)
    {
        uint32_t align = port_u8(&port, 0, L_ALIGN_X);
        ebx = set8h(ebx, align);
        switch (align)
        {
            case 0:
                edx = high(&port, L_BOTTOM);
                eax = half(edx) + high(&port, L_OFFSET_Y);
                ecx = eax;
                break;
            case 1:
                ecx = set16(ecx, port_u16(&port, 0, L_LEFT));
                break;
            case 2:
                ecx = set16(ecx, port_u16(&port, 0, L_RIGHT));
                break;
            case 3:
                ecx = set16(ecx, port_u16(&port, 0, L_ANCHOR_X));
                break;
            default:
                ecx = 0;
                break;
        }
        eax = set16(eax, port_u16(&port, 0, L_OFFSET_X));
        ecx -= eax;
        align = port_u8(&port, 0, L_ALIGN_Y);
        eax = set8h(eax, align);
        switch (align)
        {
            case 0:
                edx = high(&port, L_WIDTH);
                eax = half(edx) + high(&port, L_LEFT);
                ebx = eax;
                break;
            case 1:
                ebx = set16(ebx, port_u16(&port, 0, L_TOP));
                break;
            case 2:
                eax = set16(eax, port_u16(&port, 0, L_TOP));
                ebx = set16(ebx, port_u16(&port, 0, L_HEIGHT));
                ebx += eax;
                ebx--;
                break;
            case 3:
                ebx = edi;
                break;
            default:
                ebx = 0;
                break;
        }
        eax = set16(eax, port_u16(&port, 0, L_OFFSET_Y));
    }
    else
    {
        /* Scaled by sixteenths: the scaled box and offsets. */
        uint32_t width;
        uint32_t height;
        uint32_t align;
        eax = port_u32(&port, 0, L_IMAGE);
        edx = set16(edx, port_u16(&port, eax, IMAGE_WIDTH));
        eax = set16(eax, port_u16(&port, eax, IMAGE_HEIGHT));
        port_set16(&port, 0, L_SOURCE_HEIGHT, eax);
        width = edx & 0xffff;
        port_set16(&port, 0, L_SOURCE_WIDTH, edx);
        scale = ebx & 0xff;
        edx = (width >> 4) * scale;
        ebx = set16(ebx, port_u16(&port, 0, L_SOURCE_WIDTH));
        ebx = set8h(ebx, 0);
        ebx = set8(ebx, ebx & 0xf);
        port_set16(&port, 0, L_SCALED_WIDTH, edx);
        ecx = ebx & 0xffff;
        esi = set16(esi, port_u16(&port, 0, L_SCALED_WIDTH));
        ebx = set8(ebx, port_u8(&port, SCALE_REMAINDERS, scale * 16 + ecx));
        esi += ebx;
        height = port_u16(&port, 0, L_SOURCE_HEIGHT);
        ebx = height;
        ecx = (uint32_t)((int32_t)ebx >> 4);
        eax = scale * ecx;
        port_set16(&port, 0, L_SCALED_WIDTH, esi);
        esi = eax + scaled(&port, height, scale);
        edx = high(&port, L_ANCHOR_DEPTH);
        ecx = high(&port, L_SCALED_BOTTOM);
        eax = divide(edx * ecx, width);
        edx = high(&port, L_SCREEN_HEIGHT) - eax;
        port_set16(&port, 0, L_SCALED_LEFT, edx);
        eax = divide((uint32_t)(int32_t)(int16_t)esi * high(&port, L_ORIGIN_X), ebx);
        edx = (uint32_t)(int32_t)(int16_t)edi - eax - high(&port, L_SAVED_DI);
        eax = set16(eax, port_u16(&port, 0, L_SCALED_LEFT));
        port_set16(&port, 0, L_SCALED_TOP, edx);
        eax = set16(eax, eax + port_u16(&port, 0, L_SCALED_WIDTH));
        eax--;
        port_set16(&port, 0, L_SCALED_RIGHT, eax);
        eax = set16(eax, port_u16(&port, 0, L_SCALED_TOP));
        eax += esi;
        eax--;
        align = port_u8(&port, 0, L_ALIGN_X);
        ebx = set8h(ebx, align);
        port_set16(&port, 0, L_SCALED_BOTTOM, eax);
        switch (align)
        {
            case 0:
                eax = half(ecx) + high(&port, L_HEIGHT);
                ecx = eax;
                break;
            case 1:
                ecx = set16(ecx, port_u16(&port, 0, L_SCALED_LEFT));
                break;
            case 2:
                ecx = set16(ecx, port_u16(&port, 0, L_SCALED_RIGHT));
                break;
            case 3:
                ecx = set16(ecx, port_u16(&port, 0, L_ANCHOR_X));
                break;
            default:
                ecx = 0;
                break;
        }
        align = port_u8(&port, 0, L_ALIGN_Y);
        eax = set8h(eax, align);
        switch (align)
        {
            case 0:
                ebx = half((uint32_t)(int32_t)(int16_t)esi) + high(&port, L_SCALED_LEFT);
                break;
            case 1:
                ebx = set16(ebx, port_u16(&port, 0, L_SCALED_TOP));
                break;
            case 2:
                ebx = set16(ebx, port_u16(&port, 0, L_SCALED_TOP));
                ebx += esi;
                ebx--;
                break;
            case 3:
                ebx = edi;
                break;
            default:
                ebx = 0;
                break;
        }
        port_set16(&port, 0, L_SCALED_OFFSET_X,
                   divide(high(&port, L_ALIGN_X) * high(&port, L_SCALED_BOTTOM),
                          port_u16(&port, 0, L_SOURCE_WIDTH)));
        eax = divide((uint32_t)(int32_t)(int16_t)esi * high(&port, L_OFFSET_X),
                     port_u16(&port, 0, L_SOURCE_HEIGHT));
        port_set16(&port, 0, L_SCALED_OFFSET_Y, eax);
        eax = set16(eax, port_u16(&port, 0, L_SCALED_OFFSET_X));
        ecx -= eax;
        eax = set16(eax, port_u16(&port, 0, L_SCALED_OFFSET_Y));
    }
    ebx -= eax;
    /* Store the actor's position and depth. */
    eax = edi - ebx;
    port_set16(&port, 0, L_DEPTH, eax);
    eax = port_u32(&port, 0, L_ACTOR);
    port_set16(&port, eax, ACTOR_X, ecx);
    port_set16(&port, eax, ACTOR_Y, edi);
    ebx = edi;
    port_set16(&port, eax, ACTOR_DEPTH, port_u16(&port, 0, L_DEPTH));
done:
    port_set32(&port, 0, L_ANCHOR, anchor);
    port_set16(&port, 0, L_SAVED_DI, edi);
    port_set16(&port, 0, L_SAVED_SI, esi);
    port_set16(&port, 0, L_SAVED_CX, ecx);
    port_set16(&port, 0, L_SAVED_BX, ebx);
    return port_return(&port, eax, entry->edx);
}

uint32_t vertrix_port_ui_slide_sideways(PORT_SIGNATURE)
{
    Port port;
    uint8_t stack[8 + 8];
    uint32_t panel = entry->eax;
    uint32_t offset;
    uint32_t edx;
    uint32_t x;
    port_open_arguments(&port, stack, calls, services, globals, entry, 0, 2);
    offset = port_u32(&port, entry->esp, 4);
    edx = (entry->edx & 0xffff0000u) | port_u16(&port, panel, 0x16);
    port_set16(&port, panel, 0x18, edx);
    port_set16(&port, panel, 0x1c, edx);
    edx = (edx & 0xffff0000u) | port_u16(&port, panel, 0xe);
    port_set16(&port, panel, 0x10, edx);
    if (entry->edx == 1)
    {
        /* From the left: to -ebx - 4 + offset. */
        x = 0 - entry->ebx - 4 + offset;
    }
    else
    {
        /* From the right: past the screen width (0x5b9c8e). */
        x = ((edx & 0xffff0000u) | port_u16(&port, 0, 0x5b9c8e)) + 4 + offset;
        edx = x;
    }
    port_set16(&port, panel, 0xe, x);
    port_set16(&port, panel, 0x14, x);
    port_set16(&port, panel, 0x12, 8);
    port_set16(&port, panel, 0x1a, 8);
    return port_return(&port, panel, edx);
}

uint32_t vertrix_port_point_heading(PORT_SIGNATURE)
{
    enum
    {
        DELTA_X = 0x598dd8,
        DELTA_Y = 0x598dda,
        HEADING = 0x598ddc,
        GUESS = 0x598de0,
        NEXT = 0x598de4,
        CHANGE = 0x598de8,
        SQUARE = 0x598dec,
        FRACTION_X = 0x598df0,
        FRACTION_LENGTH = 0x598df4,
        RATIO = 0x598df8
    };
    Port port;
    uint32_t ebx = entry->ebx - entry->eax;
    uint32_t ecx = entry->ecx - entry->edx;
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    port_open(&port, calls, services, globals, entry);
    port_set16(&port, 0, DELTA_X, ebx);
    port_set16(&port, 0, DELTA_Y, ecx);
    if ((ebx & 0xffff) == 0 && (ecx & 0xffff) == 0)
    {
        port_set16(&port, 0, HEADING, ebx);
    }
    else
    {
        int32_t dx = (int16_t)port_u16(&port, 0, DELTA_X);
        int32_t dy = (int16_t)port_u16(&port, 0, DELTA_Y);
        uint32_t guess = 1;
        uint32_t next;
        int32_t change;
        uint32_t length;
        /* The distance by Newton's method on dx * dx + dy * dy, to within one. */
        port_set32(&port, 0, SQUARE, (uint32_t)(dx * dx) + (uint32_t)(dy * dy));
        do
        {
            next = (port_u32(&port, 0, SQUARE) / guess + guess) >> 1;
            port_set32(&port, 0, GUESS, guess);
            port_set32(&port, 0, NEXT, next);
            change = (int32_t)(next - guess);
            change = change < 0 ? -change : change;
            port_set32(&port, 0, CHANGE, (uint32_t)change);
            guess = next;
        } while (change > 1);
        port_set32(&port, 0, GUESS, next);
        length = next << 16;
        /* The angle whose cosine is |dx| / length (0x4849f0, 0x4845d0), negated for negative dx
         * and mirrored to 360 - angle for positive dy. */
        if (dx < 0)
        {
            uint32_t ratio;
            eax = (uint32_t)(-dx) << 16;
            port_set32(&port, 0, FRACTION_LENGTH, length);
            port_set32(&port, 0, FRACTION_X, eax);
            ratio = port_call(&port, 0x4849f0, eax, length, ebx, ecx);
            port_set32(&port, 0, RATIO, ratio);
            edx = 0u - ratio;
            port_set32(&port, 0, RATIO, edx);
        }
        else
        {
            eax = (uint32_t)dx << 16;
            port_set32(&port, 0, FRACTION_LENGTH, length);
            port_set32(&port, 0, FRACTION_X, eax);
            port_set32(&port, 0, RATIO, port_call(&port, 0x4849f0, eax, length, ebx, ecx));
            edx = vertrix_lift_edx;
        }
        eax = port_call(&port, 0x4845d0, port_u32(&port, 0, RATIO), edx, ebx, ecx);
        edx = (uint32_t)(int32_t)(int16_t)port_u16(&port, 0, DELTA_Y);
        port_set16(&port, 0, HEADING, eax);
        if ((int32_t)edx > 0)
        {
            edx = 0x168 - eax;
            port_set16(&port, 0, HEADING, edx);
        }
    }
    return port_return(&port, (eax & 0xffff0000u) | port_u16(&port, 0, HEADING), edx);
}

uint32_t vertrix_port_object_construct_labeled_box(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x38,
        GUARD_HANDLER = 0x4ec1ec,
        BOX_GUARD = 0x518360
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t object = entry->eax;
    uint32_t base;
    uint32_t box;
    uint32_t offset;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x34u, port.env.chain);
    port_set32(&port, ebp, -0x30u, GUARD_HANDLER);
    port_set32(&port, ebp, -0x2cu, BOX_GUARD);
    port_set32(&port, ebp, -0x28u, 0);
    port_set8(&port, ebp, -0x1cu, 0);
    port_set32(&port, ebp, -0x20u, object);
    /* The base object (0x4abd70), its label string at +0x15c (0x4ca070, then 0x5110b7). */
    base = port_call(&port, 0x4abd70, object, GUARD_HANDLER, BOX_GUARD, object);
    port_set32(&port, ebp, -0x28u, 1);
    box = port_call(&port, 0x4ca070, base + 0x15c, vertrix_lift_edx, BOX_GUARD, object) - 0x15c;
    port_set32(&port, ebp, -0x28u, 2);
    port_set32(&port, box, 0x158, 0x518404);
    port_call(&port, 0x4ca370, box + 0x15c, 0x5110b7, BOX_GUARD, box);
    port_set8(&port, box, 0x160, 0);
    for (offset = 0x162; offset <= 0x170; offset += 2)
    {
        port_set16(&port, box, offset, 0);
    }
    port_set8(&port, box, 0x94, 0);
    port_set8(&port, box, 0x95, 3);
    port_set16(&port, box, 0x172, 0);
    port_set16(&port, box, 0x17a, 0xff9c);
    port_set16(&port, box, 0x17c, 0xff9c);
    port_set32(&port, box, 0x174, 0);
    return port_return(&port, box, entry->edx);
}

uint32_t vertrix_port_object_place_label(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x28,
        GUARD_HANDLER = 0x4ec1ec,
        PLACE_GUARD = 0x517c2c
    };
    Port port;
    uint8_t stack[BELOW + 8 + 2 * 4];
    uint32_t ebp = entry->esp - 4;
    uint32_t object = entry->eax;
    uint32_t text = ebp - 0x10;
    uint32_t label;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 2);
    port_set32(&port, ebp, -0x24u, port.env.chain);
    port_set32(&port, ebp, -0x20u, GUARD_HANDLER);
    port_set32(&port, ebp, -0x1cu, PLACE_GUARD);
    port_set32(&port, ebp, -0x18u, 0);
    port_call(&port, 0x4ca070, text, entry->edx, entry->ebx, entry->ecx);
    port_set32(&port, ebp, -0x18u, 1);
    port_set32(&port, object, 0x160, vertrix_lift_edx);
    port_set16(&port, object, 0x164, entry->ebx);
    port_set16(&port, object, 0x166, entry->ecx);
    port_set32(&port, object, 0x168, port_u32(&port, ebp, 8));
    port_set32(&port, object, 0x16c, port_u32(&port, ebp, 0xc));
    label = port_u32(&port, object, 0x160);
    if (label != 0)
    {
        /* The label's text drawn at the object's position plus the offsets (+0x164, +0x166), or
         * against its far edges (+0xf4, +0xf8) when +0x168 or +0x16c is set (0x4b65d0). */
        uint32_t x;
        uint32_t y;
        uint32_t left;
        uint32_t top;
        uint32_t arguments[3];
        port_call(&port, 0x4ca370, text, port_u32(&port, label, 0x15c), entry->ebx, entry->ecx);
        port_set8(&port, ebp, -0xcu, port_u8(&port, port_u32(&port, object, 0x160), 0x160));
        if (port_u32(&port, object, 0x168) == 0)
        {
            x = port_u16(&port, object, 0xe) + port_u16(&port, object, 0x164);
            left = x;
        }
        else
        {
            left = port_u16(&port, object, 0xe);
            x = port_u16(&port, object, 0xf4) + left - 1;
        }
        if (port_u32(&port, object, 0x16c) == 0)
        {
            y = port_u16(&port, object, 0x16) + port_u16(&port, object, 0x166);
            top = y;
        }
        else
        {
            top = port_u16(&port, object, 0x16);
            y = port_u16(&port, object, 0xf8) + top - 1;
        }
        arguments[0] = (uint32_t)(int32_t)(int16_t)x;
        arguments[1] = (uint32_t)(int32_t)(int16_t)top;
        arguments[2] = (uint32_t)(int32_t)(int16_t)y;
        ebx = (uint32_t)(int32_t)(int8_t)port_u8(&port, ebp, -0xcu);
        ecx = (uint32_t)(int32_t)(int16_t)left;
        port_call_stack(&port, 0x4b65d0, port_u32(&port, object, 0x160), port_u32(&port, text, 0),
                        ebx, ecx, arguments, 3);
    }
    port_set32(&port, ebp, -0x18u, 0);
    port_call(&port, 0x4ca210, text, 0, ebx, ecx);
    port_set32(&port, ebp, -0x18u, 0);
    return port_return(&port, port_u32(&port, ebp, -0x24u), vertrix_lift_edx);
}

/* The box destructors' shared parts. Mode 4 destroys an array: each element by the element
 * destructor (0x4ccb9f), the block freed by 0x4ca040 (with edx 0 when `clear` is set). */
static uint32_t box_destroy_array(Port *port, uint32_t ebp, uint32_t object, uint32_t element,
                                  int clear)
{
    uint32_t block;
    port_set32(port, ebp, -0x44u, object);
    port_set32(port, ebp, -0x24u, 1);
    block = port_call(port, 0x4ccb9f, object, element, 1, object);
    port_set32(port, ebp, -0x24u, 0);
    port_call(port, 0x4ca040, block, clear ? 0 : vertrix_lift_edx, 1, object);
    return port_return(port, object, vertrix_lift_edx);
}

/* Otherwise the method table is set at +0x158 and a guard record is entered in the state given. */
static void box_destroy_enter(Port *port, uint32_t ebp, uint32_t object, uint32_t mode,
                              uint32_t table, uint32_t guard, uint32_t state)
{
    port_set32(port, object, 0x158, table);
    port_set32(port, ebp, -0x1cu, object);
    port_set8(port, ebp, -0x18u, mode);
    port_set32(port, ebp, -0x30u, port->env.chain);
    port_set32(port, ebp, -0x2cu, 0x4ec1ec);
    port_set32(port, ebp, -0x28u, guard);
    port_set32(port, ebp, -0x24u, state);
}

/* The base destructor's result is freed by 0x4ca050 when mode 2 is set. */
static uint32_t box_destroy_free(Port *port, uint32_t result, uint32_t edx, uint32_t mode)
{
    if (mode & 2)
    {
        port_call(port, 0x4ca050, result, edx, mode, result);
        edx = vertrix_lift_edx;
    }
    return port_return(port, result, edx);
}

uint32_t vertrix_port_object_destroy_call(PORT_SIGNATURE)
{
    Port port;
    uint8_t stack[0x48 + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t object = entry->eax;
    uint32_t mode = entry->edx;
    uint32_t result;
    port_open_stack(&port, stack, calls, services, globals, entry, 0x48);
    if (mode & 4)
    {
        return box_destroy_array(&port, ebp, object, 0x518190, 0);
    }
    box_destroy_enter(&port, ebp, object, mode, 0x518174, 0x518130, 0);
    result = port_call(&port, 0x4ac130, object, 1, mode, object);
    port_set32(&port, ebp, -0x24u, 0);
    return box_destroy_free(&port, result, vertrix_lift_edx, mode);
}

uint32_t vertrix_port_object_destroy_d(PORT_SIGNATURE)
{
    Port port;
    uint8_t stack[0x48 + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t object = entry->eax;
    uint32_t mode = entry->edx;
    uint32_t box;
    uint32_t result;
    port_open_stack(&port, stack, calls, services, globals, entry, 0x48);
    if (mode & 4)
    {
        return box_destroy_array(&port, ebp, object, 0x518420, 0);
    }
    box_destroy_enter(&port, ebp, object, mode, 0x518404, 0x518374, 3);
    /* The label string (+0x15c) first. */
    box = port_call(&port, 0x4ca210, object + 0x15c, 0, mode, object) - 0x15c;
    port_set32(&port, ebp, -0x24u, 0);
    result = port_call(&port, 0x4ac130, box, 1, mode, box);
    port_set32(&port, ebp, -0x24u, 0);
    return box_destroy_free(&port, result, 0, mode);
}

uint32_t vertrix_port_parser_destroy(PORT_SIGNATURE)
{
    Port port;
    uint8_t stack[0x48 + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t object = entry->eax;
    uint32_t mode = entry->edx;
    uint32_t result;
    port_open_stack(&port, stack, calls, services, globals, entry, 0x48);
    if (mode & 4)
    {
        return box_destroy_array(&port, ebp, object, 0x513f10, 0);
    }
    port_set32(&port, object, 0x14, 0x517644);
    port_set32(&port, ebp, -0x1cu, object);
    port_set8(&port, ebp, -0x18u, mode);
    port_set32(&port, ebp, -0x30u, port.env.chain);
    port_set32(&port, ebp, -0x2cu, 0x4ec1ec);
    port_set32(&port, ebp, -0x28u, 0x5175a0);
    port_set32(&port, ebp, -0x24u, 3);
    /* Its list (0x48a2d0), then the base destructor 0x4b78e0. */
    port_call(&port, 0x48a2d0, object, 0x4ec1ec, mode, object);
    port_set32(&port, ebp, -0x24u, 0);
    result = port_call(&port, 0x4b78e0, object, 0, mode, object);
    port_set32(&port, ebp, -0x24u, 0);
    return box_destroy_free(&port, result, 0, mode);
}

uint32_t vertrix_port_screen_panel_destroy(PORT_SIGNATURE)
{
    Port port;
    uint8_t stack[0x48 + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t object = entry->eax;
    uint32_t mode = entry->edx;
    uint32_t result;
    port_open_stack(&port, stack, calls, services, globals, entry, 0x48);
    if (mode & 4)
    {
        /* An array (element destructor 0x515100, freed by 0x4ca040), with the mode kept in ebx. */
        uint32_t block;
        port_set32(&port, ebp, -0x44u, object);
        port_set32(&port, ebp, -0x24u, 1);
        block = port_call(&port, 0x4ccb9f, object, 0x515100, mode, object);
        port_set32(&port, ebp, -0x24u, 0);
        port_call(&port, 0x4ca040, block, 0, mode, object);
        return port_return(&port, object, vertrix_lift_edx);
    }
    port_set32(&port, object, 0x27c, 0x5150f4);
    port_set32(&port, ebp, -0x1cu, object);
    port_set8(&port, ebp, -0x18u, mode);
    port_set32(&port, ebp, -0x30u, port.env.chain);
    port_set32(&port, ebp, -0x2cu, 0x4ec1ec);
    port_set32(&port, ebp, -0x28u, 0x51502c);
    port_set32(&port, ebp, -0x24u, 4);
    /* Its three embedded objects (+0x254, +0x240, +0x22c) are destroyed by 0x4b5dc0 in turn. */
    result = port_call(&port, 0x4b5dc0, object + 0x254, 0, mode, object);
    port_set32(&port, ebp, -0x24u, 3);
    result = port_call(&port, 0x4b5dc0, result - 0x14, 0, mode, 0);
    port_set32(&port, ebp, -0x24u, 0);
    result = port_call(&port, 0x4b5dc0, result - 0x14, 0, mode, 0) - 0x22c;
    port_set32(&port, ebp, -0x24u, 0);
    return box_destroy_free(&port, result, vertrix_lift_edx, mode);
}
