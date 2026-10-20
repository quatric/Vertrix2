/* DirectDraw 7, for games that draw their own pixels (Vertrix 2 v1.2): surfaces in guest memory
 * that the game locks and writes, copies between them (Blt, BltFast) with stretching, colour
 * fills, source colour keys and mirroring, attached back buffers that Flip shows, palettes for
 * 8-bit modes and clippers that only remember their window. The surface Flip (or a Blt to the
 * primary surface) shows is converted to 0xAARRGGBB and handed to the platform. Surfaces take the
 * display mode's pixel format: 8 bits through a palette, 16 bits as 5:6:5, 24 and 32 bits as 8:8:8.
 */

#include "win32.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum
{
    DD_OK = 0,
    DDERR_INVALIDPARAMS = 0x80070057u,
    DDERR_OUTOFMEMORY = 0x8007000eu,
    DDERR_NOTFOUND = 0x887600ffu,
    DDERR_NOCLIPLIST = 0x887600cdu,
    E_NOINTERFACE = 0x80004002u,

    /* DDSURFACEDESC2 */
    DESC_SIZE = 124,
    DDSD_CAPS = 0x1,
    DDSD_HEIGHT = 0x2,
    DDSD_WIDTH = 0x4,
    DDSD_PITCH = 0x8,
    DDSD_BACKBUFFERCOUNT = 0x20,
    DDSD_LPSURFACE = 0x800,
    DDSD_PIXELFORMAT = 0x1000,
    DDSD_CKSRCBLT = 0x10000,
    DDSD_REFRESHRATE = 0x20000,
    /* ddsCaps */
    DDSCAPS_BACKBUFFER = 0x4,
    DDSCAPS_COMPLEX = 0x8,
    DDSCAPS_FLIP = 0x10,
    DDSCAPS_FRONTBUFFER = 0x20,
    DDSCAPS_OFFSCREENPLAIN = 0x40,
    DDSCAPS_PRIMARYSURFACE = 0x200,
    DDSCAPS_SYSTEMMEMORY = 0x800,
    DDSCAPS_VIDEOMEMORY = 0x4000,
    DDSCAPS_VISIBLE = 0x8000,
    DDSCAPS_LOCALVIDMEM = 0x10000000,
    /* DDPIXELFORMAT */
    DDPF_PALETTEINDEXED8 = 0x20,
    DDPF_RGB = 0x40,
    /* Blt */
    DDBLT_COLORFILL = 0x400,
    DDBLT_DDFX = 0x800,
    DDBLT_KEYSRC = 0x8000,
    DDBLT_KEYSRCOVERRIDE = 0x10000,
    DDBLTFX_MIRRORLEFTRIGHT = 0x2,
    DDBLTFX_MIRRORUPDOWN = 0x8,
    DDBLTFAST_SRCCOLORKEY = 0x1,
    /* SetColorKey */
    DDCKEY_COLORSPACE = 0x1,
    DDCKEY_SRCBLT = 0x8,

    SURFACES = 1024,
    MODES = 9
};

typedef struct
{
    uint32_t guest; /* the COM object: its vtable, then its index here + 1 */
    uint32_t refs;
    uint32_t pixels, width, height, pitch, bits;
    uint32_t caps;
    int keyed;
    uint32_t key_low, key_high;
    uint32_t back;    /* the attached back buffer */
    uint32_t palette; /* a palette object */
    uint32_t clipper;
} Surface;

typedef struct
{
    uint32_t guest;
    uint32_t refs;
    uint32_t entries[256]; /* 0x00RRGGBB */
} Palette;

static Surface surfaces[SURFACES];
static Palette palettes[16];
static uint32_t vtable_draw, vtable_surface, vtable_clipper, vtable_palette;
static uint32_t draw_object;
static uint32_t display_width = 640, display_height = 480, display_bits = 32;
static uint32_t primary;
static uint32_t *frame;
static uint32_t frame_size;
static unsigned flips;

static const uint32_t modes[MODES][3] = {{640, 480, 8},  {640, 480, 16},  {640, 480, 32},
                                         {800, 600, 8},  {800, 600, 16},  {800, 600, 32},
                                         {1024, 768, 8}, {1024, 768, 16}, {1024, 768, 32}};

static Surface *surface_of(uint32_t guest)
{
    if (guest < 0x10000u)
    {
        return NULL;
    }
    const uint32_t index = v3_r32(guest + 4u);
    if (index == 0 || index > SURFACES || surfaces[index - 1].guest != guest)
    {
        return NULL;
    }
    return &surfaces[index - 1];
}

static Palette *palette_of(uint32_t guest)
{
    for (unsigned i = 0; i < sizeof palettes / sizeof palettes[0]; ++i)
    {
        if (palettes[i].guest == guest && guest)
        {
            return &palettes[i];
        }
    }
    return NULL;
}

static uint32_t bytes_of(const Surface *s)
{
    return s->bits == 24 ? 3u : s->bits / 8u;
}

/* --- pixels --------------------------------------------------------------------------------- */

static uint32_t get_pixel(const uint8_t *p, uint32_t bytes)
{
    switch (bytes)
    {
        case 1:
            return p[0];
        case 2:
            return (uint32_t)p[0] | (uint32_t)p[1] << 8;
        case 3:
            return (uint32_t)p[0] | (uint32_t)p[1] << 8 | (uint32_t)p[2] << 16;
        default:
            return (uint32_t)p[0] | (uint32_t)p[1] << 8 | (uint32_t)p[2] << 16 |
                   (uint32_t)p[3] << 24;
    }
}

static void put_pixel(uint8_t *p, uint32_t bytes, uint32_t v)
{
    p[0] = (uint8_t)v;
    if (bytes > 1)
    {
        p[1] = (uint8_t)(v >> 8);
    }
    if (bytes > 2)
    {
        p[2] = (uint8_t)(v >> 16);
    }
    if (bytes > 3)
    {
        p[3] = (uint8_t)(v >> 24);
    }
}

static uint8_t *row_of(const Surface *s, uint32_t y)
{
    return MEM(s->pixels + y * s->pitch);
}

typedef struct
{
    int32_t left, top, right, bottom;
} Rect;

static Rect read_rect(uint32_t address, const Surface *s)
{
    Rect r = {0, 0, (int32_t)s->width, (int32_t)s->height};
    if (address)
    {
        r.left = (int32_t)v3_r32(address);
        r.top = (int32_t)v3_r32(address + 4u);
        r.right = (int32_t)v3_r32(address + 8u);
        r.bottom = (int32_t)v3_r32(address + 12u);
    }
    return r;
}

static void fill(Surface *d, Rect r, uint32_t color)
{
    const uint32_t bytes = bytes_of(d);
    r.left = r.left < 0 ? 0 : r.left;
    r.top = r.top < 0 ? 0 : r.top;
    r.right = r.right > (int32_t)d->width ? (int32_t)d->width : r.right;
    r.bottom = r.bottom > (int32_t)d->height ? (int32_t)d->height : r.bottom;
    for (int32_t y = r.top; y < r.bottom; ++y)
    {
        uint8_t *p = row_of(d, (uint32_t)y) + (uint32_t)r.left * bytes;
        if (bytes == 1)
        {
            memset(p, (int)color, (size_t)(r.right - r.left));
            continue;
        }
        for (int32_t x = r.left; x < r.right; ++x, p += bytes)
        {
            put_pixel(p, bytes, color);
        }
    }
}

/* Copy `sr` of `s` onto `dr` of `d`, scaled when the sizes differ, skipping source pixels in
 * [key_low, key_high] when `keyed`, mirrored by `mirror` (DDBLTFX_MIRROR*). Clipped to both. */
static void copy(Surface *d, Rect dr, const Surface *s, Rect sr, int keyed, uint32_t key_low,
                 uint32_t key_high, uint32_t mirror)
{
    const int32_t dw = dr.right - dr.left, dh = dr.bottom - dr.top;
    const int32_t sw = sr.right - sr.left, sh = sr.bottom - sr.top;
    const uint32_t bytes = bytes_of(d);
    if (dw <= 0 || dh <= 0 || sw <= 0 || sh <= 0 || bytes != bytes_of(s))
    {
        return;
    }
    const int same = dw == sw && dh == sh && !keyed && !mirror;
    for (int32_t y = 0; y < dh; ++y)
    {
        const int32_t ty = dr.top + y;
        int32_t fy = (int32_t)((int64_t)y * sh / dh);
        if (mirror & DDBLTFX_MIRRORUPDOWN)
        {
            fy = sh - 1 - fy;
        }
        fy += sr.top;
        if (ty < 0 || ty >= (int32_t)d->height || fy < 0 || fy >= (int32_t)s->height)
        {
            continue;
        }
        uint8_t *out = row_of(d, (uint32_t)ty);
        const uint8_t *in = row_of(s, (uint32_t)fy);
        if (same)
        {
            int32_t from = 0, to = dw;
            from = dr.left + from < 0 ? -dr.left : from;
            from = sr.left + from < 0 ? -sr.left : from;
            to = dr.left + to > (int32_t)d->width ? (int32_t)d->width - dr.left : to;
            to = sr.left + to > (int32_t)s->width ? (int32_t)s->width - sr.left : to;
            if (from < to)
            {
                memmove(out + (uint32_t)(dr.left + from) * bytes,
                        in + (uint32_t)(sr.left + from) * bytes, (size_t)(to - from) * bytes);
            }
            continue;
        }
        for (int32_t x = 0; x < dw; ++x)
        {
            const int32_t tx = dr.left + x;
            int32_t fx = (int32_t)((int64_t)x * sw / dw);
            if (mirror & DDBLTFX_MIRRORLEFTRIGHT)
            {
                fx = sw - 1 - fx;
            }
            fx += sr.left;
            if (tx < 0 || tx >= (int32_t)d->width || fx < 0 || fx >= (int32_t)s->width)
            {
                continue;
            }
            const uint32_t v = get_pixel(in + (uint32_t)fx * bytes, bytes);
            if (keyed && v >= key_low && v <= key_high)
            {
                continue;
            }
            put_pixel(out + (uint32_t)tx * bytes, bytes, v);
        }
    }
}

/* --- showing the primary surface ------------------------------------------------------------ */

static void show(Surface *s)
{
    if (!v3_platform->present || !s->pixels)
    {
        return;
    }
    const uint32_t n = s->width * s->height;
    if (n > frame_size)
    {
        frame = v3_grow(frame, n * sizeof *frame, "the DirectDraw frame");
        frame_size = n;
    }
    const Palette *pal = palette_of(s->palette);
    const uint32_t bytes = bytes_of(s);
    for (uint32_t y = 0; y < s->height; ++y)
    {
        const uint8_t *in = row_of(s, y);
        uint32_t *out = frame + y * s->width;
        for (uint32_t x = 0; x < s->width; ++x, in += bytes)
        {
            const uint32_t v = get_pixel(in, bytes);
            uint32_t rgb;
            switch (s->bits)
            {
                case 8:
                    rgb = pal ? pal->entries[v] : v * 0x010101u;
                    break;
                case 16:
                    rgb = ((v >> 11) & 31u) * 255u / 31u << 16 |
                          ((v >> 5) & 63u) * 255u / 63u << 8 | (v & 31u) * 255u / 31u;
                    break;
                default:
                    rgb = v & 0xffffffu;
                    break;
            }
            out[x] = 0xff000000u | rgb;
        }
    }
    const V3Frame f = {s->width, s->height, frame};
    v3_platform->present(&f);
    if (++flips % 300 == 0)
    {
        v3_log("ddraw: frame %u, heap %u KB", flips, v3_heap_used() >> 10);
    }
}

/* --- descriptions --------------------------------------------------------------------------- */

static void write_format(uint32_t at, uint32_t bits)
{
    for (uint32_t i = 0; i < 32; i += 4)
    {
        v3_w32(at + i, 0);
    }
    v3_w32(at, 32);
    v3_w32(at + 12u, bits);
    if (bits == 8)
    {
        v3_w32(at + 4u, DDPF_RGB | DDPF_PALETTEINDEXED8);
        return;
    }
    v3_w32(at + 4u, DDPF_RGB);
    if (bits == 16)
    {
        v3_w32(at + 16u, 0xf800u);
        v3_w32(at + 20u, 0x07e0u);
        v3_w32(at + 24u, 0x001fu);
    }
    else
    {
        v3_w32(at + 16u, 0x00ff0000u);
        v3_w32(at + 20u, 0x0000ff00u);
        v3_w32(at + 24u, 0x000000ffu);
    }
}

static void write_mode(uint32_t desc, uint32_t width, uint32_t height, uint32_t bits)
{
    for (uint32_t i = 0; i < DESC_SIZE; i += 4)
    {
        v3_w32(desc + i, 0);
    }
    v3_w32(desc, DESC_SIZE);
    v3_w32(desc + 4u, DDSD_HEIGHT | DDSD_WIDTH | DDSD_PITCH | DDSD_PIXELFORMAT | DDSD_REFRESHRATE);
    v3_w32(desc + 8u, height);
    v3_w32(desc + 12u, width);
    v3_w32(desc + 16u, width * (bits == 24 ? 3u : bits / 8u));
    v3_w32(desc + 24u, 60);
    write_format(desc + 72u, bits);
}

static void write_desc(uint32_t desc, const Surface *s)
{
    write_mode(desc, s->width, s->height, s->bits);
    v3_w32(desc + 4u, DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PITCH | DDSD_PIXELFORMAT |
                          DDSD_LPSURFACE | (s->back ? DDSD_BACKBUFFERCOUNT : 0) |
                          (s->keyed ? DDSD_CKSRCBLT : 0));
    v3_w32(desc + 16u, s->pitch);
    v3_w32(desc + 20u, s->back ? 1u : 0u);
    v3_w32(desc + 24u, 0);
    v3_w32(desc + 36u, s->pixels);
    v3_w32(desc + 64u, s->key_low);
    v3_w32(desc + 68u, s->key_high);
    v3_w32(desc + 104u, s->caps);
}

/* --- objects -------------------------------------------------------------------------------- */

static Surface *surface_new(uint32_t width, uint32_t height, uint32_t bits, uint32_t caps)
{
    for (unsigned i = 0; i < SURFACES; ++i)
    {
        Surface *s = &surfaces[i];
        if (s->guest)
        {
            continue;
        }
        const uint32_t pitch = (width * (bits == 24 ? 3u : bits / 8u) + 3u) & ~3u;
        const uint32_t pixels = v3_alloc_aligned(pitch * height, 32);
        const uint32_t guest = v3_alloc(8);
        if (!pixels || !guest)
        {
            v3_log("ddraw: no memory for a %ux%u surface", width, height);
            if (pixels)
            {
                v3_free(pixels);
            }
            if (guest)
            {
                v3_free(guest);
            }
            return NULL;
        }
        memset(MEM(pixels), 0, pitch * height);
        memset(s, 0, sizeof *s);
        s->guest = guest;
        s->refs = 1;
        s->pixels = pixels;
        s->width = width;
        s->height = height;
        s->pitch = pitch;
        s->bits = bits;
        s->caps = caps;
        v3_w32(guest, vtable_surface);
        v3_w32(guest + 4u, i + 1u);
        return s;
    }
    v3_log("ddraw: out of surfaces");
    return NULL;
}

static void surface_free(Surface *s)
{
    if (s->back)
    {
        Surface *b = surface_of(s->back);
        if (b)
        {
            surface_free(b);
        }
    }
    if (s->guest == primary)
    {
        primary = 0;
    }
    v3_free(s->pixels);
    v3_w32(s->guest + 4u, 0);
    v3_free(s->guest);
    memset(s, 0, sizeof *s);
}

static void unimplemented(Cpu *c)
{
    v3_log("unimplemented DirectDraw method %s", v3_host_current);
    v3_trap(c, v3_r32(c->esp), "unimplemented DirectDraw method");
}

static void QueryInterface(Cpu *c)
{
    /* Every interface the game asks of an object is the one it has (IDirectDraw7, the surface's
     * IDirectDrawSurface7). */
    v3_w32(ARG(2), ARG(0));
    STDCALL_RETURN(3, DD_OK);
}

static void AddRef(Cpu *c)
{
    Surface *s = surface_of(ARG(0));
    STDCALL_RETURN(1, s ? ++s->refs : 2);
}

static void Release(Cpu *c)
{
    Surface *s = surface_of(ARG(0));
    if (!s)
    {
        STDCALL_RETURN(1, 0);
    }
    const uint32_t refs = --s->refs;
    if (refs == 0)
    {
        surface_free(s);
    }
    STDCALL_RETURN(1, refs);
}

static void Ok1(Cpu *c)
{
    STDCALL_RETURN(1, DD_OK);
}

static void Ok2(Cpu *c)
{
    STDCALL_RETURN(2, DD_OK);
}

static void Ok3(Cpu *c)
{
    STDCALL_RETURN(3, DD_OK);
}

/* --- IDirectDraw7 --------------------------------------------------------------------------- */

static void DD_CreateClipper(Cpu *c)
{
    if (!vtable_clipper)
    {
        v3_fatal("no clipper vtable");
    }
    const uint32_t clipper = v3_system_alloc(8);
    v3_w32(clipper, vtable_clipper);
    v3_w32(ARG(2), clipper);
    STDCALL_RETURN(4, DD_OK);
}

static void DD_CreatePalette(Cpu *c)
{
    const uint32_t flags = ARG(1), entries = ARG(2), out = ARG(3);
    for (unsigned i = 0; i < sizeof palettes / sizeof palettes[0]; ++i)
    {
        Palette *p = &palettes[i];
        if (p->guest)
        {
            continue;
        }
        p->guest = v3_system_alloc(8);
        p->refs = 1;
        v3_w32(p->guest, vtable_palette);
        const unsigned n = (flags & 0x4u) ? 256u : 16u; /* DDPCAPS_8BIT */
        for (unsigned k = 0; k < n && entries; ++k)
        {
            const uint32_t e = v3_r32(entries + 4u * k); /* PALETTEENTRY: r, g, b, flags */
            p->entries[k] = (e & 0xffu) << 16 | (e & 0xff00u) | (e >> 16 & 0xffu);
        }
        v3_w32(out, p->guest);
        STDCALL_RETURN(5, DD_OK);
    }
    STDCALL_RETURN(5, DDERR_OUTOFMEMORY);
}

static void DD_CreateSurface(Cpu *c)
{
    const uint32_t desc = ARG(1), out = ARG(2);
    const uint32_t flags = v3_r32(desc + 4u);
    const uint32_t caps = (flags & DDSD_CAPS) ? v3_r32(desc + 104u) : 0;
    uint32_t width = (flags & DDSD_WIDTH) ? v3_r32(desc + 12u) : display_width;
    uint32_t height = (flags & DDSD_HEIGHT) ? v3_r32(desc + 8u) : display_height;
    uint32_t bits = (flags & DDSD_PIXELFORMAT) ? v3_r32(desc + 84u) : display_bits;
    if (caps & DDSCAPS_PRIMARYSURFACE)
    {
        width = display_width;
        height = display_height;
        bits = display_bits;
    }
    if (bits != 8 && bits != 16 && bits != 24 && bits != 32)
    {
        bits = display_bits;
    }
    Surface *s = surface_new(width, height, bits, caps | DDSCAPS_VIDEOMEMORY | DDSCAPS_LOCALVIDMEM);
    if (!s)
    {
        v3_w32(out, 0);
        STDCALL_RETURN(4, DDERR_OUTOFMEMORY);
    }
    if (caps & DDSCAPS_PRIMARYSURFACE)
    {
        primary = s->guest;
        s->caps |= DDSCAPS_VISIBLE | DDSCAPS_FRONTBUFFER;
        if ((flags & DDSD_BACKBUFFERCOUNT) && v3_r32(desc + 20u))
        {
            Surface *b = surface_new(width, height, bits,
                                     DDSCAPS_BACKBUFFER | DDSCAPS_FLIP | DDSCAPS_COMPLEX |
                                         DDSCAPS_VIDEOMEMORY | DDSCAPS_LOCALVIDMEM);
            if (!b)
            {
                surface_free(s);
                v3_w32(out, 0);
                STDCALL_RETURN(4, DDERR_OUTOFMEMORY);
            }
            s->back = b->guest;
        }
    }
    if (flags & DDSD_CKSRCBLT)
    {
        s->keyed = 1;
        s->key_low = v3_r32(desc + 64u);
        s->key_high = v3_r32(desc + 68u);
    }
    v3_log("ddraw: CreateSurface(%ux%u, %u bits, caps %08x%s) -> %08x", width, height, bits, caps,
           s->back ? ", back buffer" : "", s->guest);
    v3_w32(out, s->guest);
    STDCALL_RETURN(4, DD_OK);
}

static void DD_EnumDisplayModes(Cpu *c)
{
    const uint32_t context = ARG(3), callback = ARG(4);
    static uint32_t desc;
    if (!desc)
    {
        desc = v3_system_alloc(DESC_SIZE);
    }
    for (unsigned i = 0; i < MODES; ++i)
    {
        write_mode(desc, modes[i][0], modes[i][1], modes[i][2]);
        const uint32_t arguments[2] = {desc, context};
        if (v3_call_guest(c, callback, 2, arguments, 0) == 0) /* DDENUMRET_CANCEL */
        {
            break;
        }
    }
    STDCALL_RETURN(5, DD_OK);
}

static void DD_GetCaps(Cpu *c)
{
    for (unsigned k = 0; k < 2; ++k)
    {
        const uint32_t caps = ARG(1 + k);
        if (!caps)
        {
            continue;
        }
        uint32_t size = v3_r32(caps);
        size = size && size <= 0x200u ? size : 380u;
        for (uint32_t i = 4; i + 4 <= size; i += 4)
        {
            v3_w32(caps + i, 0);
        }
        /* DDCAPS_BLT, BLTCOLORFILL, BLTSTRETCH, COLORKEY, PALETTE */
        v3_w32(caps + 4u, 0x40u | 0x04000000u | 0x200u | 0x400000u | 0x800u);
        v3_w32(caps + 12u, 0x200u);                            /* dwCKeyCaps: DDCKEYCAPS_SRCBLT */
        v3_w32(caps + 16u, 0x2u | 0x8u | 0x20000u | 0x40000u); /* mirroring, stretching */
        v3_w32(caps + 60u, 32u << 20);                         /* dwVidMemTotal */
        v3_w32(caps + 64u, 28u << 20);                         /* dwVidMemFree */
    }
    STDCALL_RETURN(3, DD_OK);
}

static void DD_GetDisplayMode(Cpu *c)
{
    write_mode(ARG(1), display_width, display_height, display_bits);
    STDCALL_RETURN(2, DD_OK);
}

static void DD_SetDisplayMode(Cpu *c)
{
    display_width = ARG(1);
    display_height = ARG(2);
    display_bits = ARG(3);
    v3_log("ddraw: SetDisplayMode(%ux%u, %u bits)", display_width, display_height, display_bits);
    STDCALL_RETURN(6, DD_OK);
}

static void DD_SetCooperativeLevel(Cpu *c)
{
    v3_log("ddraw: SetCooperativeLevel(%08x)", ARG(2));
    STDCALL_RETURN(3, DD_OK);
}

static void DD_GetAvailableVidMem(Cpu *c)
{
    if (ARG(2))
    {
        v3_w32(ARG(2), 32u << 20);
    }
    if (ARG(3))
    {
        v3_w32(ARG(3), 28u << 20);
    }
    STDCALL_RETURN(4, DD_OK);
}

static void DD_GetMonitorFrequency(Cpu *c)
{
    v3_w32(ARG(1), 60);
    STDCALL_RETURN(2, DD_OK);
}

static void DD_GetVerticalBlankStatus(Cpu *c)
{
    v3_w32(ARG(1), 1);
    STDCALL_RETURN(2, DD_OK);
}

static void DD_GetScanLine(Cpu *c)
{
    v3_w32(ARG(1), 0);
    STDCALL_RETURN(2, DD_OK);
}

static void DD_GetFourCCCodes(Cpu *c)
{
    v3_w32(ARG(1), 0);
    STDCALL_RETURN(3, DD_OK);
}

static void DD_GetDeviceIdentifier(Cpu *c)
{
    for (uint32_t i = 0; i < 1072; i += 4)
    {
        v3_w32(ARG(1) + i, 0);
    }
    v3_write_string(ARG(1), "display", 512);
    v3_write_string(ARG(1) + 512u, "DirectDraw", 512);
    STDCALL_RETURN(3, DD_OK);
}

static void DD_GetGDISurface(Cpu *c)
{
    v3_w32(ARG(1), primary);
    STDCALL_RETURN(2, primary ? DD_OK : DDERR_NOTFOUND);
}

static void DD_WaitForVerticalBlank(Cpu *c)
{
    STDCALL_RETURN(3, DD_OK);
}

/* --- IDirectDrawSurface7 -------------------------------------------------------------------- */

static void S_Blt(Cpu *c)
{
    Surface *d = surface_of(ARG(0));
    Surface *s = surface_of(ARG(2));
    const uint32_t flags = ARG(4), fx = ARG(5);
    if (!d)
    {
        STDCALL_RETURN(6, DDERR_INVALIDPARAMS);
    }
    const Rect dr = read_rect(ARG(1), d);
    if (flags & DDBLT_COLORFILL)
    {
        fill(d, dr, fx ? v3_r32(fx + 80u) : 0);
    }
    else if (s)
    {
        int keyed = 0;
        uint32_t low = 0, high = 0;
        if ((flags & DDBLT_KEYSRCOVERRIDE) && fx)
        {
            keyed = 1;
            low = v3_r32(fx + 92u);
            high = v3_r32(fx + 96u);
        }
        else if ((flags & DDBLT_KEYSRC) && s->keyed)
        {
            keyed = 1;
            low = s->key_low;
            high = s->key_high;
        }
        const uint32_t mirror = (flags & DDBLT_DDFX) && fx ? v3_r32(fx + 4u) : 0;
        copy(d, dr, s, read_rect(ARG(3), s), keyed, low, high, mirror);
    }
    if (d->guest == primary)
    {
        show(d);
    }
    STDCALL_RETURN(6, DD_OK);
}

static void S_BltFast(Cpu *c)
{
    Surface *d = surface_of(ARG(0));
    Surface *s = surface_of(ARG(3));
    const uint32_t trans = ARG(5);
    if (!d || !s)
    {
        STDCALL_RETURN(6, DDERR_INVALIDPARAMS);
    }
    const Rect sr = read_rect(ARG(4), s);
    const int32_t x = (int32_t)ARG(1), y = (int32_t)ARG(2);
    const Rect dr = {x, y, x + sr.right - sr.left, y + sr.bottom - sr.top};
    const int keyed = (trans & DDBLTFAST_SRCCOLORKEY) && s->keyed;
    copy(d, dr, s, sr, keyed, s->key_low, s->key_high, 0);
    if (d->guest == primary)
    {
        show(d);
    }
    STDCALL_RETURN(6, DD_OK);
}

static void S_Flip(Cpu *c)
{
    Surface *s = surface_of(ARG(0));
    Surface *b = s ? surface_of(s->back) : NULL;
    if (s && b)
    {
        /* The back buffer's pixels become the front's; the back keeps them (as a blitting flip
         * leaves them), which the game cannot tell from a swap that it redraws over. */
        memcpy(MEM(s->pixels), MEM(b->pixels), s->pitch * s->height);
        show(s);
    }
    STDCALL_RETURN(3, DD_OK);
}

static void S_GetAttachedSurface(Cpu *c)
{
    Surface *s = surface_of(ARG(0));
    if (!s || !s->back)
    {
        v3_w32(ARG(2), 0);
        STDCALL_RETURN(3, DDERR_NOTFOUND);
    }
    ++surface_of(s->back)->refs;
    v3_w32(ARG(2), s->back);
    STDCALL_RETURN(3, DD_OK);
}

static void S_GetCaps(Cpu *c)
{
    Surface *s = surface_of(ARG(0));
    for (uint32_t i = 0; i < 16; i += 4)
    {
        v3_w32(ARG(1) + i, 0);
    }
    v3_w32(ARG(1), s ? s->caps : 0);
    STDCALL_RETURN(2, DD_OK);
}

static void S_GetColorKey(Cpu *c)
{
    Surface *s = surface_of(ARG(0));
    if (!s || !s->keyed)
    {
        STDCALL_RETURN(3, 0x887600d7u); /* DDERR_NOCOLORKEY */
    }
    v3_w32(ARG(2), s->key_low);
    v3_w32(ARG(2) + 4u, s->key_high);
    STDCALL_RETURN(3, DD_OK);
}

static void S_SetColorKey(Cpu *c)
{
    Surface *s = surface_of(ARG(0));
    const uint32_t flags = ARG(1), key = ARG(2);
    if (s && (flags & DDCKEY_SRCBLT))
    {
        s->keyed = key != 0;
        if (key)
        {
            s->key_low = v3_r32(key);
            s->key_high = (flags & DDCKEY_COLORSPACE) ? v3_r32(key + 4u) : s->key_low;
        }
    }
    STDCALL_RETURN(3, DD_OK);
}

static void S_GetPixelFormat(Cpu *c)
{
    Surface *s = surface_of(ARG(0));
    write_format(ARG(1), s ? s->bits : display_bits);
    STDCALL_RETURN(2, DD_OK);
}

static void S_GetSurfaceDesc(Cpu *c)
{
    Surface *s = surface_of(ARG(0));
    if (!s)
    {
        STDCALL_RETURN(2, DDERR_INVALIDPARAMS);
    }
    write_desc(ARG(1), s);
    STDCALL_RETURN(2, DD_OK);
}

static void S_Lock(Cpu *c)
{
    Surface *s = surface_of(ARG(0));
    if (!s)
    {
        STDCALL_RETURN(5, DDERR_INVALIDPARAMS);
    }
    write_desc(ARG(2), s);
    if (ARG(1))
    {
        const Rect r = read_rect(ARG(1), s);
        v3_w32(ARG(2) + 36u,
               s->pixels + (uint32_t)r.top * s->pitch + (uint32_t)r.left * bytes_of(s));
    }
    STDCALL_RETURN(5, DD_OK);
}

static void S_Unlock(Cpu *c)
{
    STDCALL_RETURN(2, DD_OK);
}

static void S_GetDC(Cpu *c)
{
    /* A device context GDI draws nothing into. */
    v3_w32(ARG(1), 0x00dc0100u);
    STDCALL_RETURN(2, DD_OK);
}

static void S_IsLost(Cpu *c)
{
    STDCALL_RETURN(1, DD_OK);
}

static void S_GetFlipStatus(Cpu *c)
{
    STDCALL_RETURN(2, DD_OK);
}

static void S_SetPalette(Cpu *c)
{
    Surface *s = surface_of(ARG(0));
    if (s)
    {
        s->palette = ARG(1);
    }
    STDCALL_RETURN(2, DD_OK);
}

static void S_GetPalette(Cpu *c)
{
    Surface *s = surface_of(ARG(0));
    v3_w32(ARG(1), s ? s->palette : 0);
    STDCALL_RETURN(2, s && s->palette ? DD_OK : 0x88760083u); /* DDERR_NOPALETTEATTACHED */
}

static void S_SetClipper(Cpu *c)
{
    Surface *s = surface_of(ARG(0));
    if (s)
    {
        s->clipper = ARG(1);
    }
    STDCALL_RETURN(2, DD_OK);
}

static void S_GetDDInterface(Cpu *c)
{
    v3_w32(ARG(1), draw_object);
    STDCALL_RETURN(2, DD_OK);
}

/* --- clipper and palette -------------------------------------------------------------------- */

static void C_GetHWnd(Cpu *c)
{
    v3_w32(ARG(1), v3_r32(ARG(0) + 4u));
    STDCALL_RETURN(2, DD_OK);
}

static void C_SetHWnd(Cpu *c)
{
    v3_w32(ARG(0) + 4u, ARG(2));
    STDCALL_RETURN(3, DD_OK);
}

static void C_GetClipList(Cpu *c)
{
    STDCALL_RETURN(4, DDERR_NOCLIPLIST);
}

static void C_IsClipListChanged(Cpu *c)
{
    v3_w32(ARG(1), 0);
    STDCALL_RETURN(2, DD_OK);
}

static void P_GetCaps(Cpu *c)
{
    v3_w32(ARG(1), 0x4u | 0x40u); /* DDPCAPS_8BIT, DDPCAPS_ALLOW256 */
    STDCALL_RETURN(2, DD_OK);
}

static void P_GetEntries(Cpu *c)
{
    Palette *p = palette_of(ARG(0));
    const uint32_t base = ARG(2), count = ARG(3), out = ARG(4);
    for (uint32_t i = 0; p && i < count && base + i < 256; ++i)
    {
        const uint32_t e = p->entries[base + i];
        v3_w32(out + 4u * i, (e >> 16 & 0xffu) | (e & 0xff00u) | (e & 0xffu) << 16);
    }
    STDCALL_RETURN(5, p ? DD_OK : DDERR_INVALIDPARAMS);
}

static void P_SetEntries(Cpu *c)
{
    Palette *p = palette_of(ARG(0));
    const uint32_t base = ARG(2), count = ARG(3), in = ARG(4);
    for (uint32_t i = 0; p && i < count && base + i < 256; ++i)
    {
        const uint32_t e = v3_r32(in + 4u * i);
        p->entries[base + i] = (e & 0xffu) << 16 | (e & 0xff00u) | (e >> 16 & 0xffu);
    }
    STDCALL_RETURN(5, p ? DD_OK : DDERR_INVALIDPARAMS);
}

static void P_Release(Cpu *c)
{
    Palette *p = palette_of(ARG(0));
    STDCALL_RETURN(1, p && p->refs > 1 ? --p->refs : 0);
}

/* --- creation ------------------------------------------------------------------------------- */

typedef struct
{
    unsigned slot;
    const char *name;
    V3Code code;
} Method;

static uint32_t make_vtable(const char *interface, unsigned slots, const Method *methods)
{
    const uint32_t table = v3_system_alloc(4 * slots);
    for (unsigned i = 0; i < slots; ++i)
    {
        V3Code code = unimplemented;
        const char *name = "?";
        for (const Method *m = methods; m->name; ++m)
        {
            if (m->slot == i)
            {
                code = m->code;
                name = m->name;
            }
        }
        char *label = malloc(96);
        snprintf(label, 96, "%s::%s#%u", interface, name, i);
        v3_w32(table + 4 * i, v3_host_function(label, code));
    }
    return table;
}

static void make_vtables(void)
{
    static const Method draw[] = {{0, "QueryInterface", QueryInterface},
                                  {1, "AddRef", AddRef},
                                  {2, "Release", Release},
                                  {3, "Compact", Ok1},
                                  {4, "CreateClipper", DD_CreateClipper},
                                  {5, "CreatePalette", DD_CreatePalette},
                                  {6, "CreateSurface", DD_CreateSurface},
                                  {8, "EnumDisplayModes", DD_EnumDisplayModes},
                                  {10, "FlipToGDISurface", Ok1},
                                  {11, "GetCaps", DD_GetCaps},
                                  {12, "GetDisplayMode", DD_GetDisplayMode},
                                  {13, "GetFourCCCodes", DD_GetFourCCCodes},
                                  {14, "GetGDISurface", DD_GetGDISurface},
                                  {15, "GetMonitorFrequency", DD_GetMonitorFrequency},
                                  {16, "GetScanLine", DD_GetScanLine},
                                  {17, "GetVerticalBlankStatus", DD_GetVerticalBlankStatus},
                                  {18, "Initialize", Ok2},
                                  {19, "RestoreDisplayMode", Ok1},
                                  {20, "SetCooperativeLevel", DD_SetCooperativeLevel},
                                  {21, "SetDisplayMode", DD_SetDisplayMode},
                                  {22, "WaitForVerticalBlank", DD_WaitForVerticalBlank},
                                  {23, "GetAvailableVidMem", DD_GetAvailableVidMem},
                                  {25, "RestoreAllSurfaces", Ok1},
                                  {26, "TestCooperativeLevel", Ok1},
                                  {27, "GetDeviceIdentifier", DD_GetDeviceIdentifier},
                                  {0, NULL, NULL}};
    static const Method surface[] = {{0, "QueryInterface", QueryInterface},
                                     {1, "AddRef", AddRef},
                                     {2, "Release", Release},
                                     {5, "Blt", S_Blt},
                                     {7, "BltFast", S_BltFast},
                                     {11, "Flip", S_Flip},
                                     {12, "GetAttachedSurface", S_GetAttachedSurface},
                                     {13, "GetBltStatus", Ok2},
                                     {14, "GetCaps", S_GetCaps},
                                     {16, "GetColorKey", S_GetColorKey},
                                     {17, "GetDC", S_GetDC},
                                     {18, "GetFlipStatus", S_GetFlipStatus},
                                     {20, "GetPalette", S_GetPalette},
                                     {21, "GetPixelFormat", S_GetPixelFormat},
                                     {22, "GetSurfaceDesc", S_GetSurfaceDesc},
                                     {24, "IsLost", S_IsLost},
                                     {25, "Lock", S_Lock},
                                     {26, "ReleaseDC", Ok2},
                                     {27, "Restore", Ok1},
                                     {28, "SetClipper", S_SetClipper},
                                     {29, "SetColorKey", S_SetColorKey},
                                     {31, "SetPalette", S_SetPalette},
                                     {32, "Unlock", S_Unlock},
                                     {36, "GetDDInterface", S_GetDDInterface},
                                     {37, "PageLock", Ok2},
                                     {38, "PageUnlock", Ok2},
                                     {0, NULL, NULL}};
    static const Method clipper[] = {{0, "QueryInterface", QueryInterface},
                                     {1, "AddRef", AddRef},
                                     {2, "Release", Release},
                                     {3, "GetClipList", C_GetClipList},
                                     {4, "GetHWnd", C_GetHWnd},
                                     {5, "Initialize", Ok3},
                                     {6, "IsClipListChanged", C_IsClipListChanged},
                                     {7, "SetClipList", Ok3},
                                     {8, "SetHWnd", C_SetHWnd},
                                     {0, NULL, NULL}};
    static const Method palette[] = {{0, "QueryInterface", QueryInterface},
                                     {1, "AddRef", AddRef},
                                     {2, "Release", P_Release},
                                     {3, "GetCaps", P_GetCaps},
                                     {4, "GetEntries", P_GetEntries},
                                     {6, "SetEntries", P_SetEntries},
                                     {0, NULL, NULL}};
    vtable_draw = make_vtable("IDirectDraw7", 30, draw);
    vtable_surface = make_vtable("IDirectDrawSurface7", 49, surface);
    vtable_clipper = make_vtable("IDirectDrawClipper", 9, clipper);
    vtable_palette = make_vtable("IDirectDrawPalette", 7, palette);
}

/* DirectDrawCreateEx(guid, out, iid, outer) */
static void DirectDrawCreateEx(Cpu *c)
{
    if (!vtable_draw)
    {
        make_vtables();
        draw_object = v3_system_alloc(8);
        v3_w32(draw_object, vtable_draw);
    }
    v3_log("DirectDrawCreateEx -> %08x", draw_object);
    v3_w32(ARG(1), draw_object);
    STDCALL_RETURN(4, DD_OK);
}

const V3Export v3_ddraw[] = {{"DirectDrawCreateEx", DirectDrawCreateEx}, {NULL, NULL}};
