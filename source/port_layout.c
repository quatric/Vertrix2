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
