#include "rtlactorclips.h"

/* Whether a point hits an actor: the point inside the actor's rectangle (moved by its image's
 * offsets, scaled when the shade at 0x5bb738 is not 16, clipped to the clip box) and, for an
 * image of kind 1, on a pixel whose alpha byte is not 0. Leaves the rectangle in the blit globals
 * at 0x5bb6xx and 0x5bb7xx. */

enum
{
    /* The frame: 0x48 bytes below the return slot, the point's words at +0x2c and +0x30 (read
     * back as dwords, with the two bytes above each the caller left). */
    BELOW = 0x48,
    POINT_X = 0x2c,
    POINT_Y = 0x30,

    /* The actor's fields. */
    ACTOR_X = 0xe,
    ACTOR_Y = 0x16,
    ACTOR_OFFSET_Y = 0x1e,
    ACTOR_SHADE = 0x44,
    ACTOR_CLIP = 0x8e,
    ACTOR_BOX = 0xa8,
    ACTOR_IMAGE = 0xb4,
    ACTOR_WIDTH = 0xf4,
    ACTOR_HEIGHT = 0xf8,

    /* The image's fields. */
    IMAGE_PIXELS = 0x0,
    IMAGE_WIDTH = 0x4,
    IMAGE_HEIGHT = 0x8,
    IMAGE_ORIGIN_X = 0xc,
    IMAGE_ORIGIN_Y = 0x10,
    IMAGE_LEFT = 0x14,
    IMAGE_TOP = 0x18,
    IMAGE_SPAN_WIDTH = 0x1c,
    IMAGE_SPAN_HEIGHT = 0x20,
    IMAGE_KIND = 0x25,
    IMAGE_BLEND = 0x27,

    /* The globals the original saves and restores (the scaled hit test leaves its walk there). */
    SAVED_COUNT = 0x5bb700,
    SAVED_SOURCE = 0x5bb764,
    SAVED_COLUMNS = 0x5bb7d4,
    SAVED_ROWS = 0x5bb7d8,

    /* The blit globals. */
    IMAGE = 0x5bb734,
    START_X = 0x5bb7a4,
    START_Y = 0x5bb7a6,
    MAP_X = 0x5bb740,
    MAP_Y = 0x5bb742,
    LEFT = 0x5bb7a0,
    TOP = 0x5bb7a2,
    OFFSET_Y = 0x5bb7ae,
    CLIP = 0x5bbffe,
    SHADE = 0x5bb738,
    ORIGIN_X = 0x5bb7b0,
    ORIGIN_Y = 0x5bb7b2,
    BLEND = 0x5bb731,
    WIDTH = 0x5bb7b4,
    HEIGHT = 0x5bb7b6,
    SPAN_WIDTH = 0x5bb6e0,
    SPAN_HEIGHT = 0x5bb6e2,
    IMAGE_X = 0x5bb6e4,
    IMAGE_Y = 0x5bb6e6,
    KIND = 0x5bbfff,
    POINT_LEFT = 0x5bb6e8,
    POINT_TOP = 0x5bb6ea,
    UNMOVED_LEFT = 0x5bb6ec,
    UNMOVED_TOP = 0x5bb6ee,
    RIGHT = 0x5bb748,
    BOTTOM = 0x5bb74a,
    SCALED_LEFT = 0x5bb6f0,
    SCALED_TOP = 0x5bb6f2,
    SCALED_RIGHT = 0x5bb6f4,
    SCALED_BOTTOM = 0x5bb6f6,
    SCALED_WIDTH = 0x5bb6f8,
    SCALED_HEIGHT = 0x5bb6fa,
    SCALED_SPAN_WIDTH = 0x5bb6fc,
    SCALED_SPAN_HEIGHT = 0x5bb6fe,
    ROW_SUM = 0x5bb702,
    BOX_LEFT = 0x5bbff6,
    BOX_RIGHT = 0x5bbff8,
    BOX_TOP = 0x5bbffa,
    BOX_BOTTOM = 0x5bbffc,

    /* The screen size the clip modes 0 and 1 clip to. */
    SCREEN_HEIGHT = 0x5b9c90,
    SCREEN_WIDTH = 0x5b9c8e,

    /* The scale tables: 16 remainders per shade, and 1024 steps per shade. */
    SCALE_TABLE = 0x5c1b00,
    STEP_TABLE = 0x5c1c00
};

/* The registers whose leftover bits reach the result (eax), the top (bx) and the saved walk. */
typedef struct
{
    Port *port;
    uint32_t actor;
    uint32_t frame;
    uint32_t eax;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t edx;
    uint32_t esi;
    uint32_t edi;
    uint32_t ebp;
} Hit;

static uint32_t g8(Hit *h, uint32_t address)
{
    return port_u8(h->port, address, 0);
}

static uint32_t g16(Hit *h, uint32_t address)
{
    return port_u16(h->port, address, 0);
}

static int32_t s16(Hit *h, uint32_t address)
{
    return (int16_t)port_u16(h->port, address, 0);
}

static uint32_t g32(Hit *h, uint32_t address)
{
    return port_u32(h->port, address, 0);
}

static void set8(Hit *h, uint32_t address, uint32_t value)
{
    port_set8(h->port, address, 0, value);
}

static void set16(Hit *h, uint32_t address, uint32_t value)
{
    port_set16(h->port, address, 0, value);
}

static void set32(Hit *h, uint32_t address, uint32_t value)
{
    port_set32(h->port, address, 0, value);
}

/* A register's low word or byte replaced. */
static uint32_t low16(uint32_t reg, uint32_t value)
{
    return (reg & 0xffff0000u) | (value & 0xffffu);
}

static uint32_t low8(uint32_t reg, uint32_t value)
{
    return (reg & 0xffffff00u) | (value & 0xffu);
}

static int32_t word(uint32_t reg)
{
    return (int16_t)reg;
}

/* The point's dwords (its word and the two bytes above it) and its signed words. */
static uint32_t point_x(Hit *h)
{
    return port_u32(h->port, h->frame, POINT_X);
}

static uint32_t point_y(Hit *h)
{
    return port_u32(h->port, h->frame, POINT_Y);
}

/* eax = (a * b) / divisor and edx the remainder, as the original's imul, cdq and idiv: a divisor
 * of 0 leaves the product and its sign. */
static void scale(Hit *h, int32_t a, int32_t b, uint32_t divisor)
{
    const int32_t product = (int32_t)((uint32_t)a * (uint32_t)b);
    h->eax = (uint32_t)product;
    h->edx = product < 0 ? 0xffffffffu : 0;
    if (divisor != 0)
    {
        h->eax = (uint32_t)(int32_t)((int64_t)product / (int32_t)divisor);
        h->edx = (uint32_t)(int32_t)((int64_t)product % (int32_t)divisor);
    }
}

/* The image's sizes and offsets (and kind) into the blit globals. */
static void image_sizes(Hit *h, uint32_t image)
{
    h->edx = low16(h->edx, port_u16(h->port, image, IMAGE_WIDTH));
    set16(h, WIDTH, h->edx);
    h->edx = low16(h->edx, port_u16(h->port, image, IMAGE_HEIGHT));
    set16(h, HEIGHT, h->edx);
    h->edx = low16(h->edx, port_u16(h->port, image, IMAGE_SPAN_WIDTH));
    set16(h, SPAN_WIDTH, h->edx);
    h->edx = low16(h->edx, port_u16(h->port, image, IMAGE_SPAN_HEIGHT));
    set16(h, SPAN_HEIGHT, h->edx);
    h->edx = low16(h->edx, port_u16(h->port, image, IMAGE_LEFT));
    set16(h, IMAGE_X, h->edx);
    h->edx = low16(h->edx, port_u16(h->port, image, IMAGE_TOP));
}

/* The clip box of clip modes 0 and 1 (the screen, from 0, edx 0), and of mode 3 (the actor's
 * box); the other modes keep the box there is. */
static void screen_box(Hit *h, uint32_t right, uint32_t bottom)
{
    set16(h, BOX_RIGHT, right);
    set16(h, BOX_TOP, h->edx);
    set16(h, BOX_BOTTOM, bottom);
}

static void actor_box(Hit *h)
{
    h->eax = low16(h->actor, port_u16(h->port, h->actor, ACTOR_BOX));
    set16(h, BOX_LEFT, h->eax);
    h->eax = low16(h->actor, port_u16(h->port, h->actor, ACTOR_BOX + 2));
    set16(h, BOX_RIGHT, h->eax);
    h->eax = low16(h->actor, port_u16(h->port, h->actor, ACTOR_BOX + 4));
    set16(h, BOX_TOP, h->eax);
    h->eax = low16(h->actor, port_u16(h->port, h->actor, ACTOR_BOX + 6));
    set16(h, BOX_BOTTOM, h->eax);
}

/* The unscaled test (shade 16). Returns the result byte. */
static uint32_t hit_unscaled(Hit *h)
{
    const uint32_t image = g32(h, IMAGE);
    h->edx = image;
    if (image != 0)
    {
        h->eax = image;
        image_sizes(h, image);
        h->eax = low8(image, port_u8(h->port, image, IMAGE_KIND));
        set16(h, IMAGE_Y, h->edx);
        set8(h, KIND, h->eax);
    }
    else
    {
        h->eax = low16(h->actor, port_u16(h->port, h->actor, ACTOR_WIDTH));
        h->edx = 0;
        set16(h, WIDTH, h->eax);
        set16(h, IMAGE_Y, 0);
        h->eax = low16(h->actor, port_u16(h->port, h->actor, ACTOR_HEIGHT));
        set16(h, IMAGE_X, 0);
        set16(h, HEIGHT, h->eax);
        h->eax = low16(h->eax, g16(h, WIDTH));
        set16(h, SPAN_WIDTH, h->eax);
        h->eax = low16(h->eax, g16(h, HEIGHT));
        set8(h, KIND, 0);
        set16(h, SPAN_HEIGHT, h->eax);
    }

    /* The rectangle: the start less the image's origin (and the top less the offset), moved by
     * the image's offsets. */
    h->eax = low16(h->eax, g16(h, ORIGIN_X));
    h->edx = low16(h->edx, g16(h, LEFT));
    h->edx -= h->eax;
    h->eax = low16(h->eax, g16(h, ORIGIN_Y));
    set16(h, LEFT, h->edx);
    h->ebx -= h->eax;
    h->eax = low16(h->eax, g16(h, OFFSET_Y));
    set16(h, UNMOVED_LEFT, h->edx);
    h->ebx -= h->eax;
    h->eax = low16(h->eax, g16(h, IMAGE_X));
    set16(h, UNMOVED_TOP, h->ebx);
    h->edx += h->eax;
    h->eax = low16(h->eax, g16(h, IMAGE_Y));
    set16(h, LEFT, h->edx);
    h->ebx += h->eax;
    h->eax = low16(h->edx, h->edx + g16(h, SPAN_WIDTH)) - 1;
    h->edx = low16(h->edx, g16(h, SPAN_HEIGHT));
    set16(h, RIGHT, h->eax);
    h->eax = h->ebx + h->edx - 1;
    set16(h, BOTTOM, h->eax);

    if (g8(h, CLIP) != 2)
    {
        h->eax = low16(h->eax, g16(h, SCREEN_HEIGHT)) - 1;
        const uint32_t bottom = h->eax;
        h->eax = low16(h->eax, g16(h, SCREEN_WIDTH)) - 1;
        const uint32_t right = h->eax;
        const uint32_t clip = g8(h, CLIP);
        h->eax = (h->eax & 0xffff00ffu) | (clip << 8);
        if (clip == 0 || clip == 1)
        {
            h->eax = clip == 1 ? 0 : h->eax & 0xffffff00u;
            set16(h, BOX_LEFT, h->eax);
            h->eax = right;
            h->edx = 0;
            screen_box(h, right, bottom);
            h->eax = bottom;
        }
        else if (clip == 3)
        {
            actor_box(h);
        }

        /* Outside the box: no hit. */
        h->eax = low16(h->eax, g16(h, LEFT));
        if (s16(h, LEFT) > s16(h, BOX_RIGHT))
        {
            return 0;
        }
        h->eax = low16(h->eax, g16(h, RIGHT));
        if (s16(h, RIGHT) < s16(h, BOX_LEFT))
        {
            return 0;
        }
        if (word(h->ebx) > s16(h, BOX_BOTTOM))
        {
            return 0;
        }
        h->eax = low16(h->eax, g16(h, BOTTOM));
        h->edx = low16(h->edx, g16(h, BOX_TOP));
        if (s16(h, BOTTOM) < word(h->edx))
        {
            return 0;
        }
        if (word(h->ebx) < word(h->edx))
        {
            h->ebx = h->edx;
        }
        h->eax = low16(h->eax, g16(h, LEFT));
        h->edx = low16(h->edx, g16(h, BOX_LEFT));
        if (word(h->eax) < word(h->edx))
        {
            set16(h, LEFT, h->edx);
        }
        h->eax = low16(h->eax, g16(h, BOTTOM));
        h->edx = low16(h->edx, g16(h, BOX_BOTTOM));
        if (word(h->eax) > word(h->edx))
        {
            set16(h, BOTTOM, h->edx);
        }
        h->eax = low16(h->eax, g16(h, RIGHT));
        h->edx = low16(h->edx, g16(h, BOX_RIGHT));
        if (word(h->eax) > word(h->edx))
        {
            set16(h, RIGHT, h->edx);
        }
    }

    /* The point inside the rectangle. */
    const uint32_t x = point_x(h);
    const uint32_t y = point_y(h);
    set16(h, POINT_LEFT, x);
    h->eax = y;
    h->edx = low16(h->edx, g16(h, LEFT));
    set16(h, POINT_TOP, y);
    if (word(h->edx) > word(x) || word(h->ebx) > word(y))
    {
        return 0;
    }
    h->eax = x;
    if (word(x) > s16(h, RIGHT))
    {
        return 0;
    }
    h->eax = y;
    if (word(y) > s16(h, BOTTOM))
    {
        return 0;
    }
    if (g8(h, KIND) != 1)
    {
        return 1;
    }

    /* Kind 1: the pixel's alpha byte. */
    h->edx = (uint32_t)((word(y) - s16(h, UNMOVED_TOP)) * (int32_t)g16(h, WIDTH)) << 2;
    h->edx += g32(h, g32(h, IMAGE));
    h->esi = (((uint32_t)(word(x) - s16(h, UNMOVED_LEFT))) << 2) + h->edx;
    h->eax = g32(h, h->esi) >> 24;
    return h->eax != 0;
}

/* The scaled test (any other shade). Returns the result byte. */
static uint32_t hit_scaled(Hit *h)
{
    const uint32_t image = g32(h, IMAGE);
    h->eax = image;
    if (image == 0)
    {
        return 0;
    }
    image_sizes(h, image);
    set16(h, IMAGE_Y, h->edx);
    h->edx = low8(h->edx, port_u8(h->port, image, IMAGE_KIND));
    set8(h, KIND, h->edx);
    h->eax = low8(image, port_u8(h->port, image, IMAGE_BLEND));
    h->edx = low16(h->edx, g16(h, ORIGIN_X));
    set8(h, BLEND, h->eax);

    /* The rectangle: the start less the image's origin (and the top less the offset), moved by
     * the image's offsets. */
    h->eax = low16(h->eax, g16(h, LEFT));
    h->eax -= h->edx;
    h->edx = low16(h->edx, g16(h, IMAGE_X));
    h->edx += h->eax;
    h->eax = low16(h->eax, g16(h, ORIGIN_Y));
    set16(h, LEFT, h->edx);
    h->edx = low16(h->edx, g16(h, OFFSET_Y));
    h->ebx -= h->eax;
    h->eax = low16(h->eax, g16(h, IMAGE_Y));
    h->ebx -= h->edx;
    h->edx = low16(h->edx, g16(h, SPAN_WIDTH));
    h->ebx += h->eax;
    h->eax = low16(h->eax, g16(h, LEFT)) + h->edx - 1;
    h->edx = low16(h->edx, g16(h, SPAN_HEIGHT));
    set16(h, RIGHT, h->eax);
    h->eax = h->ebx + h->edx - 1;
    set16(h, BOTTOM, h->eax);

    /* The scaled sizes. */
    const uint32_t width = g16(h, WIDTH);
    const uint32_t shade = g8(h, SHADE);
    set16(h, SCALED_WIDTH, (width >> 4) * shade);
    set16(h, SCALED_WIDTH, g16(h, SCALED_WIDTH) + g8(h, SCALE_TABLE + shade * 16 + (width & 0xf)));
    const uint32_t height = g16(h, HEIGHT);
    set16(h, SCALED_HEIGHT, (height >> 4) * shade);
    h->edx = g16(h, SCALED_HEIGHT) + g8(h, SCALE_TABLE + shade * 16 + (height & 0xf));
    set16(h, SCALED_HEIGHT, h->edx);
    if (g16(h, SCALED_WIDTH) == 0 || (h->edx & 0xffff) == 0)
    {
        h->eax = 0;
        return 0;
    }

    /* The scaled rectangle: the start plus the rectangle's distance from it, scaled, and the
     * image's span scaled. */
    const int32_t scaled_width = s16(h, SCALED_WIDTH);
    const int32_t scaled_height = s16(h, SCALED_HEIGHT);
    const uint32_t start_x = (uint32_t)s16(h, START_X);
    scale(h, (int32_t)(start_x - (uint32_t)s16(h, LEFT)), scaled_width, width);
    set16(h, SCALED_LEFT, start_x - h->eax);
    const uint32_t start_y = (uint32_t)s16(h, START_Y);
    const uint32_t offset_y = (uint32_t)s16(h, OFFSET_Y);
    scale(h, (int32_t)(start_y - (uint32_t)word(h->ebx) - offset_y), scaled_height, height);
    set16(h, SCALED_TOP, start_y - h->eax - offset_y);
    scale(h, s16(h, SPAN_WIDTH), scaled_width, width);
    set16(h, SCALED_SPAN_WIDTH, h->eax);
    scale(h, s16(h, SPAN_HEIGHT), scaled_height, height);
    set16(h, SCALED_SPAN_HEIGHT, h->eax);
    h->edx = low16(h->edx, g16(h, SCALED_SPAN_WIDTH));
    h->eax = low16(h->eax, g16(h, SCALED_LEFT)) + h->edx - 1;
    h->edx = low16(h->edx, g16(h, SCALED_SPAN_HEIGHT));
    set16(h, SCALED_RIGHT, h->eax);
    h->eax = low16(h->eax, g16(h, SCALED_TOP)) + h->edx - 1;
    const uint32_t clip = g8(h, CLIP);
    set16(h, SCALED_BOTTOM, h->eax);

    if (clip != 2)
    {
        h->eax = low16(h->eax, g16(h, SCREEN_HEIGHT)) - 1;
        const uint32_t bottom = h->eax;
        h->eax = low16(h->eax, g16(h, SCREEN_WIDTH)) - 1;
        const uint32_t right = h->eax;
        if (clip == 0 || clip == 1)
        {
            h->eax = 0;
            set16(h, BOX_LEFT, 0);
            h->eax = right;
            h->edx = 0;
            screen_box(h, right, bottom);
            h->eax = bottom;
        }
        else if (clip == 3)
        {
            actor_box(h);
        }

        /* Outside the box: no hit. */
        h->eax = low16(h->eax, g16(h, SCALED_LEFT));
        if (s16(h, SCALED_LEFT) > s16(h, BOX_RIGHT))
        {
            return 0;
        }
        h->eax = low16(h->eax, g16(h, SCALED_RIGHT));
        if (s16(h, SCALED_RIGHT) < s16(h, BOX_LEFT))
        {
            return 0;
        }
        h->eax = low16(h->eax, g16(h, SCALED_TOP));
        if (s16(h, SCALED_TOP) > s16(h, BOX_BOTTOM))
        {
            return 0;
        }
        h->eax = low16(h->eax, g16(h, SCALED_BOTTOM));
        h->edx = low16(h->edx, g16(h, BOX_TOP));
        if (s16(h, SCALED_BOTTOM) < word(h->edx))
        {
            return 0;
        }
        if (word(h->edx) > s16(h, SCALED_TOP))
        {
            set16(h, SCALED_TOP, h->edx);
        }
        h->eax = low16(h->eax, g16(h, SCALED_LEFT));
        h->edx = low16(h->edx, g16(h, BOX_LEFT));
        if (word(h->eax) < word(h->edx))
        {
            set16(h, SCALED_LEFT, h->edx);
        }
        h->eax = low16(h->eax, g16(h, SCALED_BOTTOM));
        h->edx = low16(h->edx, g16(h, BOX_BOTTOM));
        if (word(h->eax) > word(h->edx))
        {
            set16(h, SCALED_BOTTOM, h->edx);
        }
        h->eax = low16(h->eax, g16(h, SCALED_RIGHT));
        h->edx = low16(h->edx, g16(h, BOX_RIGHT));
        if (word(h->eax) > word(h->edx))
        {
            set16(h, SCALED_RIGHT, h->edx);
        }
    }

    /* The point inside the scaled rectangle. */
    const uint32_t x = point_x(h);
    const uint32_t y = point_y(h);
    set16(h, POINT_LEFT, x);
    h->eax = y;
    set16(h, POINT_TOP, y);
    if (s16(h, SCALED_LEFT) > word(x) || word(y) < s16(h, SCALED_TOP))
    {
        return 0;
    }
    h->eax = x;
    if (word(x) > s16(h, SCALED_RIGHT))
    {
        return 0;
    }
    h->eax = y;
    if (word(y) > s16(h, SCALED_BOTTOM))
    {
        return 0;
    }
    if (g8(h, KIND) != 1)
    {
        return 1;
    }

    /* Kind 1: walk the shade's step table to the pixel, rows (a step's sum of rows times the
     * width) then columns, and test its alpha byte. */
    h->edi = (g8(h, SHADE) << 10) + STEP_TABLE;
    h->esi = g32(h, g32(h, IMAGE));
    h->ecx = low16(h->ecx, g16(h, SCALED_TOP));
    h->ebp = h->edi;
    h->ecx = low16(y, y - h->ecx);
    if ((h->ecx & 0xffff) != 0)
    {
        uint32_t sum = 0;
        set16(h, ROW_SUM, 0);
        while ((h->ecx & 0xffff) != 0)
        {
            sum = (sum + g8(h, h->edi)) & 0xffff;
            h->edi++;
            set16(h, ROW_SUM, sum);
            h->ecx = low16(h->ecx, h->ecx - 1);
        }
        h->esi += (g16(h, WIDTH) * sum) << 2;
    }
    h->ecx = low16(h->ecx, g16(h, POINT_LEFT) - g16(h, SCALED_LEFT));
    while ((h->ecx & 0xffff) != 0)
    {
        h->esi += g8(h, h->ebp) << 2;
        h->ebp++;
        h->ecx = low16(h->ecx, h->ecx - 1);
    }
    h->eax = g32(h, h->esi) >> 24;
    return h->eax != 0;
}

/* Original 0x4b0b70 (eax = the actor, dx, bx = the point). Returns in al whether the point hits
 * the actor (above al, the bits the original leaves there); leaves bx (the rectangle's top) at
 * 0x5bb7a2. */
static uint32_t hit(Hit *h, uint32_t x, uint32_t y)
{
    set16(h, h->frame + POINT_X, x);
    set16(h, h->frame + POINT_Y, y);
    const uint32_t actor = h->actor;
    set32(h, IMAGE, port_u32(h->port, actor, ACTOR_IMAGE));
    set16(h, START_X, port_u16(h->port, actor, ACTOR_X));
    set16(h, MAP_X, port_u16(h->port, actor, ACTOR_X));
    set16(h, START_Y, port_u16(h->port, actor, ACTOR_Y));
    set16(h, MAP_Y, port_u16(h->port, actor, ACTOR_Y));
    set16(h, LEFT, g16(h, START_X));
    set8(h, CLIP, port_u8(h->port, actor, ACTOR_CLIP));
    set16(h, OFFSET_Y, port_u16(h->port, actor, ACTOR_OFFSET_Y));
    h->eax = low8(actor, port_u8(h->port, actor, ACTOR_SHADE));
    h->edx = g32(h, IMAGE);
    h->ebx = low16(h->ebx, g16(h, START_Y));
    set8(h, SHADE, h->eax);
    if (h->edx != 0)
    {
        const uint32_t image = h->edx;
        h->eax = image;
        h->edx = low16(h->edx, port_u16(h->port, image, IMAGE_ORIGIN_X));
        set16(h, ORIGIN_X, h->edx);
        h->edx = low16(h->edx, port_u16(h->port, image, IMAGE_ORIGIN_Y));
        h->eax = low8(image, port_u8(h->port, image, IMAGE_BLEND));
        set16(h, ORIGIN_Y, h->edx);
        set8(h, BLEND, h->eax);
    }
    else
    {
        h->edx = 0;
        set16(h, ORIGIN_Y, 0);
        set16(h, ORIGIN_X, 0);
    }
    return g8(h, SHADE) == 0x10 ? hit_unscaled(h) : hit_scaled(h);
}

uint32_t vertrix_port_actor_draw_clipped_4b0b70(PORT_SIGNATURE)
{
    Port port;
    uint8_t stack[BELOW + 8];
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    Hit h = {.port = &port,
             .actor = entry->eax,
             .frame = entry->esp - BELOW,
             .ebx = entry->ebx,
             .ecx = low16(entry->ecx, port_u16(&port, SAVED_COUNT, 0)),
             .edx = entry->edx};
    h.esi = port_u32(&port, SAVED_SOURCE, 0);
    h.edi = port_u32(&port, SAVED_COLUMNS, 0);
    h.ebp = port_u32(&port, SAVED_ROWS, 0);
    const uint32_t result = hit(&h, entry->edx, entry->ebx);
    h.eax = low8(h.eax, result);
    set16(&h, TOP, h.ebx);
    set32(&h, SAVED_ROWS, h.ebp);
    set32(&h, SAVED_COLUMNS, h.edi);
    set32(&h, SAVED_SOURCE, h.esi);
    set16(&h, SAVED_COUNT, h.ecx);
    return port_return(&port, h.eax, h.edx);
}
