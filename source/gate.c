#include "gate.h"

enum
{
    ACTOR_DRAW_SPAN = 0x4ae110,
    CLEAR_WORDS = 0x4eb5c0,
    SURFACE_OFFSET = 0x478eb0,
    SCREEN = 0x544070,
    SCREEN_WIDTH = 0x208,
    SCREEN_HEIGHT = 0x20c,
    SCREEN_LEFT = 0x214,
    SCREEN_TOP = 0x216,
    SCREEN_SCALE_OFF = 0x220,
    SCREEN_SCALE = 0x221,
    SCREEN_TINT_OFF = 0x222,
    SCREEN_TINT_LEVEL = 0x223,
    SCREEN_TINT = 0x224,
    SCREEN_DEPTH = 0x226,
    SCREEN_TINT_MAP = 0x26c,
    SCREEN_SCALE_MAP = 0x270,
    SCREEN_COVER = 0x274,
    COVER_BITS = 3,
    SCALE_REMAINDERS = 0x5c1b00,
    SCALE_ROWS = 0x5c1c00,
    SCALE_FULL = 0x10,
    TARGET = 0x5bc010,
    TARGET_WIDTH = 0x04,
    TARGET_HEIGHT = 0x08,
    TARGET_DEPTH = 0x0c,
    TARGET_KIND = 0x0d,
    TARGET_PITCH = 0x14,
    TARGET_BITS = 0x18,
    TARGET_HIDDEN = 3,
    IMAGE_WIDTH = 0x04,
    IMAGE_HEIGHT = 0x08,
    IMAGE_ORIGIN_X = 0x0c,
    IMAGE_ORIGIN_Y = 0x10,
    IMAGE_MODE = 0x26,
    IMAGE_FLAGS = 0x27,
    ACTOR_X = 0x0e,
    ACTOR_Y = 0x16,
    ACTOR_DEPTH = 0x1e,
    ACTOR_SCALE = 0x44,
    ACTOR_TINT_LEVEL = 0x48,
    ACTOR_OPACITY = 0x4e,
    ACTOR_TINT = 0x52,
    ACTOR_FLIP = 0x80,
    ACTOR_MIRROR = 0x8c,
    ACTOR_CLIP_MODE = 0x8e,
    ACTOR_UNCOVERED = 0x8f,
    ACTOR_SCREEN_SCALE = 0x91,
    ACTOR_SCREEN_TINT = 0x92,
    ACTOR_TRANSPARENT = 0x93,
    ACTOR_BLEND_SOURCE = 0x94,
    ACTOR_BLEND_KIND = 0x95,
    ACTOR_CLIP_BOX = 0xa8,
    ACTOR_IMAGE = 0xb4,
    ACTOR_SPAN = 0x13c,
    OPAQUE = 0x64,
    CLIP_TARGET = 0,
    CLIP_TARGET_TOO = 1,
    CLIP_NONE = 2,
    CLIP_BOX = 3,
    /* The working globals (words unless noted). */
    G_PIXEL_INDEX = 0x5bb73c, /* dword: the actor's pixel on the screen */
    G_PIXEL_X = 0x5bb740,
    G_PIXEL_Y = 0x5bb742,
    G_SCREEN_WIDTH = 0x5bb744,
    G_SCREEN_HEIGHT = 0x5bb746,
    G_RIGHT = 0x5bb748,
    G_BOTTOM = 0x5bb74a,
    G_WIDTH = 0x5bb74c,
    G_HEIGHT = 0x5bb74e,
    G_VISIBLE_WIDTH = 0x5bb750,
    G_VISIBLE_HEIGHT = 0x5bb752,
    G_SOURCE_OFFSET = 0x5bb790, /* dword */
    G_TARGET_STRIDE = 0x5bb794, /* dword */
    G_TARGET_WIDTH = 0x5bb798,
    G_SOURCE_SKIP = 0x5bb79c, /* dword */
    G_LEFT = 0x5bb7a0,
    G_TOP = 0x5bb7a2,
    G_ACTOR_X = 0x5bb7a4,
    G_ACTOR_Y = 0x5bb7a6,
    G_COVER_TOP = 0x5bb7a8,
    G_COVER_BOTTOM = 0x5bb7aa,
    G_COVER_ROWS = 0x5bb7ac,
    G_DEPTH = 0x5bb7ae,
    G_ORIGIN_X = 0x5bb7b0,
    G_ORIGIN_Y = 0x5bb7b2,
    G_IMAGE_WIDTH = 0x5bb7b4,
    G_IMAGE_HEIGHT = 0x5bb7b6,
    G_FLIP = 0x5bb7b8,              /* byte */
    G_TARGET_FULL_WIDTH = 0x5bb7bc, /* dword */
    G_IMAGE_STRIDE = 0x5bb7c0,      /* dword */
    G_TARGET_PITCH = 0x5bb7c4,      /* dword */
    G_TARGET_SKIP = 0x5bb7c8,       /* dword */
    G_COVER = 0x5bb7cc,             /* dword: the cover mask byte under the actor */
    G_COVER_COLUMN = 0x5bb7d0,      /* dword */
    G_SCALE_COLUMNS = 0x5bb7d4,     /* dword */
    G_SCALE_ROWS = 0x5bb7d8,        /* dword */
    G_SCALE_SUM = 0x5bb7e0,
    G_MASK_COLUMN = 0x5bb7e4, /* dword */
    G_MASK_ROW = 0x5bb7e8,    /* dword */
    G_COLUMNS = 0x5bb7ec,     /* a word per visible column: its hidden rows */
    G_COLUMN = 0x5bbfec,      /* dword */
    G_SOURCE = 0x5bb764,      /* dword, also at 0x5bb76c */
    G_SOURCE_COPY = 0x5bb76c,
    G_TARGET_32 = 0x5bb768, /* dwords, a pair for each depth */
    G_TARGET_32_COPY = 0x5bb770,
    G_TARGET_8 = 0x5bb778,
    G_TARGET_8_COPY = 0x5bb77c,
    G_TARGET_16 = 0x5bb780,
    G_TARGET_16_COPY = 0x5bb784,
    G_COUNT = 0x5bb68a,
    G_COLUMN_COUNT = 0x5bb68c,
    G_SAVED_SI = 0x5bb68e,
    G_SCALE_SKIP = 0x5bb690,
    G_SCALED = 0x5bb694,       /* dword */
    G_CODE = 0x5bb730,         /* byte */
    G_IMAGE_FLAGS = 0x5bb731,  /* byte */
    G_TARGET_DEPTH = 0x5bb732, /* byte */
    G_TARGET_KIND = 0x5bb733,  /* byte */
    G_IMAGE = 0x5bb734,        /* dword */
    G_SCALE = 0x5bb738,        /* byte */
    G_TRANSPARENT = 0x5bb739,  /* byte */
    G_MIRROR = 0x5bb73a,       /* byte */
    G_COVERED = 0x5bbff0,      /* byte */
    G_CLIP_RIGHT_START = 0x5bbff2,
    G_CLIP_TOP_START = 0x5bbff4,
    G_CLIP_LEFT = 0x5bbff6,
    G_CLIP_RIGHT = 0x5bbff8,
    G_CLIP_TOP = 0x5bbffa,
    G_CLIP_BOTTOM = 0x5bbffc,
    G_CLIP_MODE = 0x5bbffe,  /* byte */
    G_IMAGE_MODE = 0x5bbfff, /* byte */
    G_TINT = 0x5bc000,       /* byte */
    G_TINT_LEVEL = 0x5bc002,
    G_TINT_CODE = 0x5bc004,    /* byte */
    G_UNCOVERED = 0x5bc005,    /* byte */
    G_BLEND_SOURCE = 0x5bc00c, /* byte */
    G_BLEND_KIND = 0x5bc00d,   /* byte */
    G_OPACITY = 0x5bc00e,      /* byte */
    G_CLIPPED = 0x5bc014,      /* byte */
    G_SAVED_DI = 0x5bc016
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

static int16_t s16(uint32_t value)
{
    return (int16_t)(value & 0xffff);
}

/* The globals the gate reads and writes (the screen pointer up to the working block), in place
 * where they can be: set on entry. It stays valid across the gate's calls, as the image the
 * globals lie in never moves; a nested gate sets the same window. */
enum
{
    GLOBALS_LOW = 0x544000,
    GLOBALS_HIGH = 0x5bc100
};

static PortWindow gate_globals;

static uint32_t w(Port *port, uint32_t address)
{
    return port_window_u16(port, &gate_globals, 0, address);
}

static uint32_t b(Port *port, uint32_t address)
{
    return port_window_u8(port, &gate_globals, 0, address);
}

static uint32_t d(Port *port, uint32_t address)
{
    return port_window_u32(port, &gate_globals, 0, address);
}

/* The word at `address` sign-extended (the original's `mov r, [address - 2]; sar r, 16`). */
static uint32_t sw(Port *port, uint32_t address)
{
    return (uint32_t)((int32_t)port_window_u32(port, &gate_globals, 0, address - 2) >> 16);
}

static void put8(Port *port, uint32_t address, uint32_t value)
{
    port_window_set8(port, &gate_globals, 0, address, value);
}

static void put16(Port *port, uint32_t address, uint32_t value)
{
    port_window_set16(port, &gate_globals, 0, address, value);
}

static void put32(Port *port, uint32_t address, uint32_t value)
{
    port_window_set32(port, &gate_globals, 0, address, value);
}

/* `cdq; idiv divisor`: the quotient and remainder, both unchanged when it would fault. */
static void divide(uint32_t dividend, uint32_t divisor, uint32_t *eax, uint32_t *edx)
{
    LiftFlags flags = {0, 0, 0, 0, 0, 0};
    *eax = dividend;
    *edx = (uint32_t)((int32_t)dividend >> 31);
    lift_idiv1(32, divisor, eax, edx, &flags);
}

/* `mov ax, [low]; cmp ax, [high]` style bound: the signed word is clamped to `limit - 1`. */
static uint32_t clamp_below(Port *port, uint32_t address, uint32_t *value, uint32_t limit)
{
    *value = set16(*value, w(port, address));
    if (s16(*value) >= s16(limit))
    {
        uint32_t eax = limit - 1;
        put16(port, address, eax);
        return eax;
    }
    return *value;
}

uint32_t vertrix_port_actor_gate(PORT_SIGNATURE)
{
    Port port;
    Port *p = &port;
    uint32_t actor = entry->eax;
    uint32_t gate = entry->edx;
    uint32_t eax = entry->eax;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t edx;
    uint32_t si;
    uint32_t di;
    uint32_t image;
    uint32_t screen = 0;
    uint32_t local;
    port_open(p, calls, services, globals, entry);
    gate_globals = port_window(p, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    si = w(p, G_SAVED_SI);
    di = w(p, G_SAVED_DI);
    edx = port_u32(p, actor, ACTOR_SPAN);
    if (edx == 0)
    {
        /* No span yet: 0x4ae110 makes an empty one. */
        uint32_t argument = edx;
        ebx = ecx = 0;
        port_call_stack(p, ACTOR_DRAW_SPAN, actor, edx, 0, 0, &argument, 1);
        edx = vertrix_lift_edx;
    }
    di = w(p, G_SAVED_DI);
    si = w(p, G_SAVED_SI);
    image = eax = port_u32(p, actor, ACTOR_IMAGE);
    put32(p, G_IMAGE, image);
    if (image == 0)
    {
        goto done;
    }
    ebx = d(p, TARGET);
    if (ebx == 0)
    {
        goto hidden;
    }
    /* The actor, its image and the target. */
    edx = set8(edx, port_u8(p, image, IMAGE_FLAGS));
    put8(p, G_IMAGE_FLAGS, edx);
    edx = ebx;
    ebx = set8(ebx, port_u8(p, ebx, TARGET_DEPTH));
    edx = set8(edx, port_u8(p, edx, TARGET_KIND));
    put8(p, G_TARGET_DEPTH, ebx);
    put8(p, G_TARGET_KIND, edx);
    if ((edx & 0xff) == TARGET_HIDDEN)
    {
        goto hidden;
    }
    edx = set16(actor, port_u16(p, actor, ACTOR_X));
    put16(p, G_ACTOR_X, edx);
    put16(p, G_PIXEL_X, edx);
    edx = set16(actor, port_u16(p, actor, ACTOR_Y));
    put16(p, G_ACTOR_Y, edx);
    put16(p, G_PIXEL_Y, edx);
    edx = set16(edx, w(p, G_ACTOR_X));
    put16(p, G_LEFT, edx);
    edx = set16(edx, w(p, G_ACTOR_Y));
    put16(p, G_TOP, edx);
    edx = set16(actor, port_u16(p, actor, ACTOR_DEPTH));
    put16(p, G_DEPTH, edx);
    edx = set16(edx, port_u16(p, image, IMAGE_ORIGIN_X));
    put16(p, G_ORIGIN_X, edx);
    edx = set16(edx, port_u16(p, image, IMAGE_ORIGIN_Y));
    put16(p, G_ORIGIN_Y, edx);
    edx = set16(edx, port_u16(p, image, IMAGE_WIDTH));
    put16(p, G_IMAGE_WIDTH, edx);
    edx = set16(edx, port_u16(p, image, IMAGE_HEIGHT));
    eax = set8(image, port_u8(p, image, IMAGE_MODE));
    put8(p, G_IMAGE_MODE, eax);
    eax = set8(actor, port_u8(p, actor, ACTOR_TRANSPARENT));
    put8(p, G_TRANSPARENT, eax);
    put32(p, G_SOURCE_OFFSET, 0);
    put16(p, G_IMAGE_HEIGHT, edx);
    eax = set8(actor, port_u8(p, actor, ACTOR_BLEND_SOURCE));
    edx = set8(actor, port_u8(p, actor, ACTOR_UNCOVERED));
    put8(p, G_BLEND_SOURCE, eax);
    put8(p, G_UNCOVERED, edx);
    eax = set8(actor, port_u8(p, actor, ACTOR_BLEND_KIND));
    put8(p, G_BLEND_KIND, eax);
    edx = set8(actor, port_u8(p, actor, ACTOR_CLIP_MODE));
    eax = set8(actor, port_u8(p, actor, ACTOR_OPACITY));
    put8(p, G_CLIP_MODE, edx);
    put8(p, G_OPACITY, eax);
    if ((eax & 0xff) == OPAQUE)
    {
        /* Fully opaque: no transparency. */
        ebx = set8(ebx, 0);
        put8(p, G_TRANSPARENT, 0);
    }
    eax = set8(actor, port_u8(p, actor, ACTOR_MIRROR));
    put8(p, G_MIRROR, eax);
    eax = set8(actor, port_u8(p, actor, ACTOR_FLIP));
    edx = gate;
    put8(p, G_FLIP, eax);
    if (gate == 0)
    {
        /* On the screen: its size, and the actor relative to its scrolled view. */
        screen = eax = d(p, SCREEN);
        edx = set16(edx, port_u16(p, screen, SCREEN_WIDTH));
        put16(p, G_SCREEN_WIDTH, edx);
        edx = set16(edx, port_u16(p, screen, SCREEN_HEIGHT));
        ebx = set16(ebx, w(p, G_LEFT));
        put16(p, G_SCREEN_HEIGHT, edx);
        edx = set16(edx, port_u16(p, screen, SCREEN_LEFT));
        ecx = set16(ecx, w(p, G_TOP));
        ebx -= edx;
        edx = set16(edx, port_u16(p, screen, SCREEN_TOP));
        eax = set16(eax, port_u16(p, screen, SCREEN_DEPTH));
        ecx -= edx;
        edx = set16(edx, w(p, G_DEPTH));
        put16(p, G_LEFT, ebx);
        edx += eax;
        put16(p, G_TOP, ecx);
        put16(p, G_DEPTH, edx);
    }
    ebx = set8h(ebx, 0xd);
    ecx = gate;
    put8(p, G_CODE, 0xd);
    if (gate == 0)
    {
        /* The actor's pixel, clamped into the screen. */
        eax = sw(p, G_PIXEL_X);
        if ((int32_t)eax < 0)
        {
            ecx = 0;
            put16(p, G_PIXEL_X, 0);
        }
        else
        {
            ebx = set16(ebx, w(p, G_SCREEN_WIDTH));
            eax = clamp_below(p, G_PIXEL_X, &eax, ebx);
        }
        eax = sw(p, G_PIXEL_Y);
        if ((int32_t)eax < 0)
        {
            ebx = 0;
            put16(p, G_PIXEL_Y, 0);
        }
        else
        {
            edx = set16(edx, w(p, G_SCREEN_HEIGHT));
            eax = clamp_below(p, G_PIXEL_Y, &eax, edx);
        }
        edx = sw(p, G_SCREEN_WIDTH);
        eax = sw(p, G_PIXEL_Y);
        edx *= eax;
        eax = sw(p, G_PIXEL_X);
        edx += eax;
        put32(p, G_PIXEL_INDEX, edx);
    }
    /* The scale: the screen's scale map under the actor, its fixed scale, or the actor's. */
    if (gate != 1 && port_u8(p, actor, ACTOR_SCREEN_SCALE) != 0)
    {
        screen = eax = d(p, SCREEN);
        if (port_u8(p, screen, SCREEN_SCALE_OFF) == 0)
        {
            eax = set8(screen, port_u8(p, screen, SCREEN_SCALE));
        }
        else
        {
            edx = d(p, G_PIXEL_INDEX);
            eax = port_u32(p, port_u32(p, screen, SCREEN_SCALE_MAP), 0) + edx;
            eax = set8(eax, port_u8(p, eax, 0) + 1);
        }
    }
    else
    {
        eax = set8(actor, port_u8(p, actor, ACTOR_SCALE));
    }
    put8(p, G_SCALE, eax);
    eax = b(p, G_SCALE) != SCALE_FULL;
    ecx = gate;
    put32(p, G_SCALED, eax);
    /* The tint: the screen's tint map under the actor, its fixed tint, or the actor's. */
    if (gate != 1 && port_u8(p, actor, ACTOR_SCREEN_TINT) != 0)
    {
        screen = eax = d(p, SCREEN);
        if (port_u8(p, screen, SCREEN_TINT_OFF) == 0)
        {
            edx = set16(edx, (uint32_t)(int8_t)port_u8(p, screen, SCREEN_TINT_LEVEL));
            eax = set8(screen, port_u8(p, screen, SCREEN_TINT));
            put16(p, G_TINT_LEVEL, edx);
            put8(p, G_TINT, eax);
        }
        else
        {
            /* A code: the tint in its top 5 bits, the level (-5 to 2) in its low 3, scaled by 40
             * when it brightens and 20 when it darkens. */
            ebx = d(p, G_PIXEL_INDEX);
            eax = port_u32(p, port_u32(p, screen, SCREEN_TINT_MAP), 0) + ebx;
            eax = set8(eax, port_u8(p, eax, 0));
            put8(p, G_TINT_CODE, eax);
            eax = b(p, G_TINT_CODE) >> 3;
            put8(p, G_TINT, eax);
            eax = set8(eax, ((b(p, G_TINT_CODE) & 7) - 5) & 0xff);
            edx = set16(edx, (uint32_t)(int8_t)eax);
            eax = (uint32_t)(int8_t)eax;
            put16(p, G_TINT_LEVEL, edx);
            eax = (int32_t)eax >= 0 ? edx * 0x28 : edx * 0x14;
            put16(p, G_TINT_LEVEL, eax);
        }
    }
    else
    {
        eax = set8(actor, port_u8(p, actor, ACTOR_TINT));
        put8(p, G_TINT, eax);
        eax = set16(actor, port_u16(p, actor, ACTOR_TINT_LEVEL));
        put16(p, G_TINT_LEVEL, eax);
    }
    if (d(p, G_SCALED) != 0)
    {
        /* The scaled size: whole sixteenths times the scale plus the remainder's row, and the
         * origin scaled to match. */
        ecx = w(p, G_IMAGE_WIDTH);
        eax = b(p, G_SCALE);
        edx = (uint32_t)((int32_t)ecx >> 4) * eax;
        put16(p, G_WIDTH, edx);
        local = eax << 4;
        edx = ((ecx & 0xf) & 0xffff) + local;
        edx = port_u8(p, SCALE_REMAINDERS, edx);
        ebx = set16(ebx, w(p, G_WIDTH)) + edx;
        put16(p, G_WIDTH, ebx);
        ebx = w(p, G_IMAGE_HEIGHT);
        edx = (uint32_t)((int32_t)ebx >> 4);
        eax *= edx;
        put16(p, G_HEIGHT, eax);
        eax = ((ebx & 0xf) & 0xffff) + local;
        eax = port_u8(p, SCALE_REMAINDERS, eax);
        edx = set16(edx, w(p, G_HEIGHT)) + eax;
        eax = d(p, G_BOTTOM);
        put16(p, G_HEIGHT, edx);
        edx = sw(p, G_ORIGIN_X);
        eax = sw(p, G_WIDTH);
        divide(edx * eax, ecx, &eax, &edx);
        put16(p, G_ORIGIN_X, eax);
        edx = sw(p, G_HEIGHT);
        eax = sw(p, G_ORIGIN_Y);
        divide(edx * eax, ebx, &eax, &edx);
        put16(p, G_ORIGIN_Y, eax);
    }
    else
    {
        eax = set16(eax, w(p, G_IMAGE_WIDTH));
        put16(p, G_WIDTH, eax);
        eax = set16(eax, w(p, G_IMAGE_HEIGHT));
        put16(p, G_HEIGHT, eax);
    }
    ebx = set16(ebx, w(p, G_WIDTH));
    if ((ebx & 0xffff) == 0)
    {
        goto hidden;
    }
    ecx = set16(ecx, w(p, G_HEIGHT));
    if ((ecx & 0xffff) == 0)
    {
        goto hidden;
    }
    /* The rectangle: the position less the origin (and the depth for the top). */
    eax = set16(eax, w(p, G_ORIGIN_X));
    edx = set16(edx, w(p, G_LEFT));
    put16(p, G_VISIBLE_WIDTH, ebx);
    ebx = set16(ebx, w(p, G_TOP));
    edx -= eax;
    eax = set16(eax, w(p, G_ORIGIN_Y));
    put16(p, G_VISIBLE_HEIGHT, ecx);
    ebx -= eax;
    eax = set16(eax, w(p, G_DEPTH));
    ecx = ebx;
    put16(p, G_LEFT, edx);
    ecx -= eax;
    eax = set16(edx, edx + w(p, G_WIDTH));
    put16(p, G_TOP, ebx);
    eax--;
    ebx = set16(ebx, w(p, G_HEIGHT));
    put16(p, G_RIGHT, eax);
    eax = ecx + ebx;
    put16(p, G_TOP, ecx);
    eax--;
    put16(p, G_CLIP_TOP_START, ecx);
    put16(p, G_BOTTOM, eax);
    eax = set16(eax, w(p, G_LEFT));
    ebx = set8(ebx, b(p, G_CLIP_MODE));
    put16(p, G_CLIP_RIGHT_START, eax);
    /* The clip box: the target's, the actor's own, or none. */
    if ((ebx & 0xff) != CLIP_NONE)
    {
        if ((ebx & 0xff) == CLIP_TARGET_TOO || (ebx & 0xff) == CLIP_TARGET)
        {
            if ((ebx & 0xff) == CLIP_TARGET_TOO)
            {
                ebx = 0;
            }
            else
            {
                ecx = 0;
            }
            eax = d(p, TARGET);
            put16(p, G_CLIP_LEFT, 0);
            put16(p, G_CLIP_TOP, 0);
            edx = set16(edx, port_u16(p, eax, TARGET_WIDTH));
            eax = set16(eax, port_u16(p, eax, TARGET_HEIGHT));
            edx--;
            eax--;
            put16(p, G_CLIP_RIGHT, edx);
            put16(p, G_CLIP_BOTTOM, eax);
        }
        else if ((ebx & 0xff) == CLIP_BOX)
        {
            eax = set16(actor, port_u16(p, actor, ACTOR_CLIP_BOX));
            put16(p, G_CLIP_LEFT, eax);
            eax = set16(actor, port_u16(p, actor, ACTOR_CLIP_BOX + 2));
            put16(p, G_CLIP_RIGHT, eax);
            eax = set16(actor, port_u16(p, actor, ACTOR_CLIP_BOX + 4));
            put16(p, G_CLIP_TOP, eax);
            eax = set16(actor, port_u16(p, actor, ACTOR_CLIP_BOX + 6));
            put16(p, G_CLIP_BOTTOM, eax);
        }
        /* Outside the box altogether: nothing to paint. */
        eax = set16(eax, w(p, G_LEFT));
        if (s16(eax) > s16(w(p, G_CLIP_RIGHT)))
        {
            goto hidden;
        }
        eax = set16(eax, w(p, G_RIGHT));
        if (s16(eax) < s16(w(p, G_CLIP_LEFT)))
        {
            goto hidden;
        }
        eax = set16(eax, w(p, G_TOP));
        if (s16(eax) > s16(w(p, G_CLIP_BOTTOM)))
        {
            goto hidden;
        }
        eax = set16(eax, w(p, G_BOTTOM));
        if (s16(eax) < s16(w(p, G_CLIP_TOP)))
        {
            goto hidden;
        }
    }
    eax = set8(eax, 0);
    put8(p, G_CLIPPED, 0);
    if (b(p, G_CLIP_MODE) != CLIP_NONE)
    {
        /* Cut the rectangle to the box, skipping the source rows and columns cut off. */
        eax = set16(eax, w(p, G_TOP));
        if (s16(eax) < s16(w(p, G_CLIP_TOP)))
        {
            if (d(p, G_SCALED) == 0)
            {
                edx = sw(p, G_CLIP_TOP);
                eax = sw(p, G_TOP);
                edx -= eax;
                eax = sw(p, G_WIDTH);
                eax *= edx;
                put32(p, G_SOURCE_OFFSET, d(p, G_SOURCE_OFFSET) + eax);
            }
            eax = set16(eax, w(p, G_CLIP_TOP));
            edx = set8(edx, 1);
            put16(p, G_TOP, eax);
            put8(p, G_CLIPPED, 1);
        }
        eax = set16(eax, w(p, G_LEFT));
        if (s16(eax) < s16(w(p, G_CLIP_LEFT)))
        {
            if (d(p, G_SCALED) == 0)
            {
                edx = sw(p, G_CLIP_LEFT);
                eax = sw(p, G_LEFT);
                edx -= eax;
                put32(p, G_SOURCE_OFFSET, d(p, G_SOURCE_OFFSET) + edx);
            }
            eax = set16(eax, w(p, G_CLIP_LEFT));
            edx = set8h(edx, 1);
            put16(p, G_LEFT, eax);
            put8(p, G_CLIPPED, 1);
        }
        eax = set16(eax, w(p, G_BOTTOM));
        edx = set16(edx, w(p, G_CLIP_BOTTOM));
        if (s16(eax) > s16(edx))
        {
            ebx = set8(ebx, 1);
            put16(p, G_BOTTOM, edx);
            put8(p, G_CLIPPED, 1);
        }
        eax = set16(eax, w(p, G_RIGHT));
        ebx = set16(ebx, w(p, G_CLIP_RIGHT));
        if (s16(eax) > s16(ebx))
        {
            put16(p, G_RIGHT, ebx);
            put8(p, G_CLIPPED, 1);
        }
    }
    edx = 0;
    ecx = set8(ecx, b(p, G_CLIPPED));
    put32(p, G_SOURCE_SKIP, 0);
    if ((ecx & 0xff) != 0)
    {
        /* The visible size, and the source pixels skipped at the end of each row. */
        eax = set16(eax, w(p, G_RIGHT));
        eax = set16(eax, eax - w(p, G_LEFT));
        eax++;
        edx = w(p, G_TOP);
        put16(p, G_VISIBLE_WIDTH, eax);
        eax = set16(eax, w(p, G_BOTTOM));
        eax -= edx;
        eax++;
        edx = sw(p, G_WIDTH);
        put16(p, G_VISIBLE_HEIGHT, eax);
        eax = sw(p, G_VISIBLE_WIDTH);
        edx -= eax;
        ebx = set16(ebx, w(p, G_VISIBLE_WIDTH));
        put32(p, G_SOURCE_SKIP, edx);
        if ((ebx & 0xffff) == 0 || w(p, G_VISIBLE_HEIGHT) == 0)
        {
            goto hidden;
        }
    }
    if (d(p, G_SCALED) == 1)
    {
        /* Scaled: the scale's row of 0x400 steps says how many source pixels each target pixel
         * advances; the clipped rows and columns are summed into the source offset. */
        eax = b(p, G_SCALE);
        edx = SCALE_ROWS + (eax << 10);
        ecx = set8h(ecx, b(p, G_CLIPPED));
        put32(p, G_SCALE_COLUMNS, edx);
        put32(p, G_SCALE_ROWS, edx);
        if ((ecx & 0xff00) != 0)
        {
            eax = set16(eax, w(p, G_TOP));
            edx = set16(edx, w(p, G_CLIP_TOP_START));
            eax = set16(eax, eax - edx);
            put16(p, G_COUNT, eax);
            if ((eax & 0xffff) != 0)
            {
                ecx = 0;
                put16(p, G_SCALE_SKIP, 0);
                do
                {
                    eax = d(p, G_SCALE_COLUMNS) + 1;
                    edx = set8h(edx, 0);
                    edx = set8(edx, port_u8(p, eax, -1u));
                    put32(p, G_SCALE_COLUMNS, eax);
                    eax = set16(eax, w(p, G_SCALE_SKIP));
                    eax += edx;
                    edx = set16(edx, w(p, G_COUNT));
                    put16(p, G_SCALE_SKIP, eax);
                    edx = set16(edx, edx - 1);
                    put16(p, G_COUNT, edx);
                } while ((edx & 0xffff) != 0);
                edx = eax & 0xffff;
                eax = w(p, G_IMAGE_WIDTH);
                eax *= edx;
                put32(p, G_SOURCE_OFFSET, d(p, G_SOURCE_OFFSET) + eax);
            }
            eax = set16(eax, w(p, G_LEFT));
            ecx = set16(ecx, w(p, G_CLIP_RIGHT_START));
            eax = set16(eax, eax - ecx);
            put16(p, G_COUNT, eax);
            if ((eax & 0xffff) != 0)
            {
                do
                {
                    eax = d(p, G_SCALE_ROWS) + 1;
                    edx = port_u8(p, eax, -1u);
                    put32(p, G_SCALE_ROWS, eax);
                    eax = d(p, G_SOURCE_OFFSET) + edx;
                    edx = set16(edx, w(p, G_COUNT));
                    put32(p, G_SOURCE_OFFSET, eax);
                    edx = set16(edx, edx - 1);
                    put16(p, G_COUNT, edx);
                } while ((edx & 0xffff) != 0);
            }
        }
        eax = d(p, G_SCALE_COLUMNS);
        ecx = 0;
        put32(p, G_COVER, eax);
        eax = set16(eax, w(p, G_VISIBLE_HEIGHT));
        put16(p, G_SCALE_SUM, 0);
        eax = set16(eax, eax - 1);
        put16(p, G_COUNT, eax);
        if ((eax & 0xffff) != 0)
        {
            do
            {
                eax = d(p, G_COVER);
                ebx = set16(ebx, w(p, G_SCALE_SUM));
                edx = set8h(edx, 0);
                ecx = set16(ecx, w(p, G_COUNT));
                edx = set8(edx, port_u8(p, eax, 0));
                eax++;
                ebx += edx;
                put32(p, G_COVER, eax);
                put16(p, G_SCALE_SUM, ebx);
                ecx = set16(ecx, ecx - 1);
                put16(p, G_COUNT, ecx);
            } while ((ecx & 0xffff) != 0);
        }
    }
    edx = gate;
    put16(p, G_SAVED_SI, si);
    eax = set8(eax, 0);
    put16(p, G_SAVED_DI, di);
    put8(p, G_COVERED, 0);
    if (gate == 0)
    {
        screen = eax = d(p, SCREEN);
    }
    if (gate == 0 && port_u32(p, screen, SCREEN_COVER) != 0 && b(p, G_UNCOVERED) == 0)
    {
        /* The screen's cover mask: count, per visible column, the covered rows above the actor's
         * bottom; 0x4af560 leaves those out. */
        ebx = sw(p, G_VISIBLE_WIDTH) * 2;
        eax = port_call(p, CLEAR_WORDS, G_COLUMNS, edx, ebx, ecx);
        edx = vertrix_lift_edx;
        eax = set16(eax, w(p, G_ACTOR_Y));
        edx = set16(edx, w(p, G_ORIGIN_Y));
        ebx = set16(ebx, w(p, G_HEIGHT));
        eax = eax - edx + ebx - 1;
        ecx = set16(ecx, w(p, G_DEPTH));
        put16(p, G_COVER_BOTTOM, eax);
        eax -= ecx;
        edx = set16(edx, w(p, G_ACTOR_Y));
        put16(p, G_COVER_TOP, eax);
        if (s16(edx) < s16(w(p, G_COVER_BOTTOM)))
        {
            put16(p, G_COVER_BOTTOM, edx);
        }
        eax = sw(p, G_COVER_BOTTOM);
        di = w(p, G_SAVED_DI);
        si = w(p, G_SAVED_SI);
        if ((int32_t)eax < 0)
        {
            ecx = 0;
            put16(p, G_COVER_BOTTOM, 0);
        }
        else
        {
            ebx = set16(ebx, w(p, G_SCREEN_HEIGHT));
            eax = clamp_below(p, G_COVER_BOTTOM, &eax, ebx);
        }
        eax = sw(p, G_COVER_TOP);
        if ((int32_t)eax < 0)
        {
            ebx = 0;
            put16(p, G_COVER_TOP, 0);
        }
        else
        {
            edx = set16(edx, w(p, G_SCREEN_HEIGHT));
            eax = clamp_below(p, G_COVER_TOP, &eax, edx);
        }
        eax = set16(eax, w(p, G_COVER_BOTTOM) - w(p, G_COVER_TOP));
        eax++;
        put16(p, G_COVER_ROWS, eax);
        put16(p, G_COLUMN_COUNT, 0);
        put16(p, G_COUNT, 0);
        screen = eax = d(p, SCREEN);
        ecx = sw(p, G_LEFT);
        edx = port_u32(p, port_u32(p, screen, SCREEN_COVER), 0);
        eax = set16(eax, port_u16(p, screen, SCREEN_LEFT));
        edx += ecx;
        eax &= 0xffff;
        ecx = edx + eax;
        edx = sw(p, G_SCREEN_WIDTH);
        eax = sw(p, G_COVER_BOTTOM);
        eax *= edx;
        ecx += eax;
        eax = sw(p, G_COVER_ROWS);
        put32(p, G_COVER, ecx);
        if ((int32_t)eax > 1)
        {
            /* A column is covered when its cover runs unbroken from the bottom row up. */
            ebx = set8(ebx, COVER_BITS);
            for (;;)
            {
                eax = set16(eax, w(p, G_COUNT));
                if (s16(eax) >= s16(w(p, G_VISIBLE_WIDTH)))
                {
                    break;
                }
                eax = d(p, G_COVER);
                if ((port_u8(p, eax, 0) & ebx & 0xff) != 0)
                {
                    si = w(p, G_COVER_ROWS);
                    put32(p, G_COVER_COLUMN, eax);
                    while (si != 0)
                    {
                        eax = d(p, G_COVER_COLUMN);
                        if ((port_u8(p, eax, 0) & ebx & 0xff) == 0)
                        {
                            break;
                        }
                        edx = sw(p, G_SCREEN_WIDTH);
                        eax -= edx;
                        si = (si - 1) & 0xffff;
                        put32(p, G_COVER_COLUMN, eax);
                    }
                    if (si == 0)
                    {
                        edx = 1;
                        ecx = set16(ecx, w(p, G_COLUMN_COUNT)) + edx;
                        eax = sw(p, G_COUNT);
                        put16(p, G_COLUMN_COUNT, ecx);
                        put16(p, G_COLUMNS + eax * 2, edx);
                    }
                }
                put32(p, G_COVER, d(p, G_COVER) + 1);
                put16(p, G_COUNT, w(p, G_COUNT) + 1);
            }
        }
        else
        {
            /* One row: each column covered there. */
            ecx = 1;
            for (;;)
            {
                eax = set16(eax, w(p, G_COUNT));
                if (s16(eax) >= s16(w(p, G_VISIBLE_WIDTH)))
                {
                    break;
                }
                eax = d(p, G_COVER);
                if ((port_u8(p, eax, 0) & COVER_BITS) != 0)
                {
                    eax = sw(p, G_COUNT);
                    put16(p, G_COLUMNS + eax * 2, ecx);
                    put16(p, G_COLUMN_COUNT, w(p, G_COLUMN_COUNT) + ecx);
                }
                ebx = d(p, G_COVER) + 1;
                edx = set16(edx, w(p, G_COUNT)) + 1;
                put32(p, G_COVER, ebx);
                put16(p, G_COUNT, edx);
            }
        }
        eax = set16(eax, w(p, G_COLUMN_COUNT));
        edx = set16(edx, w(p, G_VISIBLE_WIDTH));
        put16(p, G_SAVED_SI, si);
        put16(p, G_SAVED_DI, di);
        if ((eax & 0xffff) == (edx & 0xffff) || (eax & 0xffff) != 0)
        {
            ecx = set8(ecx, 1);
            di = w(p, G_SAVED_DI);
            si = w(p, G_SAVED_SI);
            put8(p, G_COVERED, 1);
            goto covered;
        }
    }
    di = w(p, G_SAVED_DI);
    ecx = set8h(ecx, b(p, G_COVERED));
    si = w(p, G_SAVED_SI);
    if ((ecx & 0xff00) == 0)
    {
        goto pointers;
    }
covered:
    /* Some columns are covered: count each one's covered rows from the actor's bottom up. */
    screen = eax = d(p, SCREEN);
    ecx = sw(p, G_LEFT);
    edx = port_u32(p, port_u32(p, screen, SCREEN_COVER), 0);
    ecx += edx;
    edx = port_u16(p, screen, SCREEN_LEFT);
    eax = set16(eax, port_u16(p, screen, SCREEN_TOP));
    ecx += edx;
    edx = sw(p, G_BOTTOM);
    eax &= 0xffff;
    edx += eax;
    eax = sw(p, G_SCREEN_WIDTH);
    eax *= edx;
    edx = G_COLUMNS;
    ecx += eax;
    eax = set16(eax, w(p, G_VISIBLE_WIDTH));
    put32(p, G_MASK_COLUMN, ecx);
    put32(p, G_COLUMN, edx);
    put16(p, G_COLUMN_COUNT, eax);
    while ((eax & 0xffff) != 0)
    {
        eax = d(p, G_COLUMN);
        if (port_u16(p, eax, 0) != 0)
        {
            di = w(p, G_VISIBLE_HEIGHT);
            edx = d(p, G_MASK_COLUMN);
            port_set16(p, eax, 0, 0);
            put32(p, G_MASK_ROW, edx);
            while (di != 0)
            {
                eax = d(p, G_MASK_ROW);
                if ((port_u8(p, eax, 0) & COVER_BITS) == 0)
                {
                    break;
                }
                ecx = sw(p, G_SCREEN_WIDTH);
                edx = d(p, G_COLUMN);
                ebx = set16(ebx, port_u16(p, edx, 0));
                eax -= ecx;
                ebx++;
                put32(p, G_MASK_ROW, eax);
                port_set16(p, edx, 0, ebx);
                di = (di - 1) & 0xffff;
            }
        }
        ecx = d(p, G_MASK_COLUMN) + 1;
        ebx = d(p, G_COLUMN) + 2;
        eax = set16(eax, w(p, G_COLUMN_COUNT));
        put32(p, G_MASK_COLUMN, ecx);
        put32(p, G_COLUMN, ebx);
        eax = set16(eax, eax - 1);
        put16(p, G_COLUMN_COUNT, eax);
    }
    screen = eax = d(p, SCREEN);
    ecx = sw(p, G_LEFT);
    edx = port_u32(p, port_u32(p, screen, SCREEN_COVER), 0);
    ecx += edx;
    edx = port_u16(p, screen, SCREEN_LEFT);
    eax = set16(eax, port_u16(p, screen, SCREEN_TOP));
    ecx += edx;
    edx = sw(p, G_TOP);
    eax &= 0xffff;
    eax += edx;
    edx = sw(p, G_SCREEN_WIDTH);
    eax *= edx;
    ecx += eax;
    put32(p, G_MASK_COLUMN, ecx);
    put32(p, G_MASK_ROW, ecx);
pointers:
    /* The source pixels and the target's: its width, pitch and the first pixel's address. */
    eax = d(p, G_SOURCE_OFFSET) << 2;
    edx = port_u32(p, d(p, G_IMAGE), 0) + eax;
    eax = d(p, TARGET);
    put32(p, G_SOURCE, edx);
    put32(p, G_SOURCE_COPY, edx);
    edx = set16(edx, port_u16(p, eax, TARGET_WIDTH));
    put16(p, G_TARGET_WIDTH, edx);
    edx = w(p, G_IMAGE_WIDTH);
    put32(p, G_IMAGE_STRIDE, edx);
    edx = sw(p, G_TARGET_WIDTH);
    ecx = sw(p, G_TARGET_WIDTH);
    put32(p, G_TARGET_FULL_WIDTH, edx);
    edx = sw(p, G_VISIBLE_WIDTH);
    ecx -= edx;
    edx = port_u32(p, eax, TARGET_PITCH);
    put32(p, G_TARGET_PITCH, edx);
    edx = b(p, G_TARGET_DEPTH) * ecx;
    put32(p, G_TARGET_STRIDE, ecx);
    ecx = port_u32(p, eax, TARGET_BITS);
    edx += ecx;
    put16(p, G_SAVED_SI, si);
    put32(p, G_TARGET_SKIP, edx);
    edx = set8h(edx, b(p, G_TARGET_DEPTH));
    put16(p, G_SAVED_DI, di);
    /* The target's first pixel, kept for the depth 0x4af560 paints at. */
    {
        uint32_t depth = (edx >> 8) & 0xff;
        uint32_t slot = depth == 4 ? G_TARGET_32 : depth == 2 ? G_TARGET_16 : G_TARGET_8;
        uint32_t copy = depth == 4   ? G_TARGET_32_COPY
                        : depth == 2 ? G_TARGET_16_COPY
                                     : G_TARGET_8_COPY;
        if (depth == 4 || depth == 2 || depth == 1)
        {
            ebx = sw(p, G_TOP);
            edx = sw(p, G_LEFT);
            eax = port_call(p, SURFACE_OFFSET, eax, edx, ebx, ecx);
            edx = vertrix_lift_edx;
            put32(p, slot, eax);
            put32(p, copy, eax);
        }
    }
    if (port_u32(p, actor, ACTOR_SPAN) == 0)
    {
        uint32_t argument = sw(p, G_VISIBLE_HEIGHT);
        ecx = sw(p, G_VISIBLE_WIDTH);
        ebx = sw(p, G_TOP);
        edx = sw(p, G_LEFT);
        port_call_stack(p, ACTOR_DRAW_SPAN, actor, edx, ebx, ecx, &argument, 1);
        edx = vertrix_lift_edx;
    }
    eax = 1;
    di = w(p, G_SAVED_DI);
    si = w(p, G_SAVED_SI);
    goto done;
hidden:
    eax = 0;
done:
    put16(p, G_SAVED_DI, di);
    put16(p, G_SAVED_SI, si);
    return port_return(p, eax, edx);
}
