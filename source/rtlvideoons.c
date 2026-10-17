#include "rtlvideoons.h"

/* Turns the video on: creates DirectDraw, takes the screen exclusively, sets the mode's size and
 * depth, creates the flipping primary surface with one back buffer and an offscreen surface, and
 * wraps the back buffer (MYBUFFER_Background) and the offscreen surface (MYBUFFER_Trans_Buffer) in
 * images (0x558c7c, 0x558c84). An 8-bit mode also gets the palette. */

enum
{
    /* Locals handed out by address, below the saved ebp. */
    BELOW = 0x11c,
    DESC = 0x9c,    /* DDSURFACEDESC2 for the surfaces created */
    LOCKED = 0x118, /* DDSURFACEDESC2 filled by Lock */
    CAPS = 0x20,    /* DDSCAPS2 of the back buffer */
    SURFACE_DESC_BYTES = 0x7c,
    DESC_FLAGS = 4,
    DESC_HEIGHT = 8,
    DESC_WIDTH = 0xc,
    DESC_PITCH = 0x10,
    DESC_BACK_BUFFERS = 0x14,
    DESC_SURFACE = 0x24,
    DESC_RED_MASK = 0x58,
    DESC_CAPS = 0x68,

    /* The display. */
    DISPLAY_RED = 0,
    DISPLAY_GREEN = 4,
    DISPLAY_BLUE = 8,
    DISPLAY_ALPHA = 0xc,
    DISPLAY_FORMAT = 0x10,
    DISPLAY_IMAGE_BYTE = 0x24,
    DISPLAY_MODE = 0x3c,
    DISPLAY_WIDTH = 0x3e,
    DISPLAY_HEIGHT = 0x40,
    DISPLAY_PITCH = 0x42,
    DISPLAY_PITCH_WORDS = 0x44,
    DISPLAY_PITCH_DWORDS = 0x46,
    DISPLAY_BYTES = 0x48,
    DISPLAY_WORDS = 0x4c,
    DISPLAY_DWORDS = 0x50,
    DISPLAY_DEPTH = 0x54,
    DISPLAY_PIXEL_BYTES = 0x56,
    DISPLAY_STATE = 0x58,
    DISPLAY_IN_VIDEO_MEMORY = 0x5c,
    DISPLAY_DDRAW = 0x60,
    DISPLAY_PRIMARY = 0x64,
    DISPLAY_BACK = 0x68,
    DISPLAY_OFFSCREEN = 0x6c,

    /* DirectDraw7 and DirectDrawSurface7 methods. */
    DDRAW_CREATE_SURFACE = 0x18,
    DDRAW_SET_COOPERATIVE_LEVEL = 0x50,
    DDRAW_SET_DISPLAY_MODE = 0x54,
    SURFACE_GET_ATTACHED = 0x30,
    SURFACE_LOCK = 0x64,
    SURFACE_UNLOCK = 0x80,

    DIRECTDRAW_CREATE_EX = 0x4f0806,
    IID_IDIRECTDRAW7 = 0x51e580,
    MAIN_WINDOW = 0x5328b4,
    WINDOW_HWND = 0x1c,
    /* DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN | DDSCL_ALLOWREBOOT | DDSCL_ALLOWMODEX */
    COOPERATIVE = 0x17,
    /* DDSD_CAPS | DDSD_BACKBUFFERCOUNT, which the original leaves in ecx from memset. */
    FLAGS_CAPS_BACK_BUFFERS = 0x21,
    CAPS_FLIP_CHAIN = 0x218, /* PRIMARYSURFACE | FLIP | COMPLEX */
    CAPS_BACK_BUFFER = 4,
    /* DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH */
    FLAGS_SIZED = 7,
    CAPS_OFFSCREEN_VIDEO = 0x4040,
    CAPS_OFFSCREEN_SYSTEM = 0x840,
    DDERR_OUTOFVIDEOMEMORY = 0x8876017c,
    DDLOCK_WAIT = 1,
    CAPS_VIDEO_MEMORY_BYTE = 0x40, /* DDSCAPS_VIDEOMEMORY, in the caps' second byte */

    MEMSET = 0x4eb5c0,
    SET_FORMAT = 0x481bc0,
    IMAGE_OVER = 0x487280,
    IMAGE_PREPARE = 0x478da0,
    IMAGE_NAME = 0x478dd0,
    BACK_IMAGE = 0x558c7c,
    BACK_NAME = 0x50fd86,
    OFFSCREEN_IMAGE = 0x558c84,
    OFFSCREEN_NAME = 0x50fe55,
    PALETTE = 0x598a30,
    PALETTE_BYTES = 0x400,
    PALETTE_CLEAR = 0x480ca0,
    PALETTE_SAVED = 0x598630,
    PALETTE_APPLY = 0x480890,
    PALETTE_ATTACH_DDRAW = 0x4808f0,
    PALETTE_ATTACH_PRIMARY = 0x480940,
    VIDEO_OFF = 0x486e20,
    REPORT = 0x485700,

    /* The messages reported. */
    FAILED_CREATE = 0x50fc3e,
    FAILED_COOPERATE = 0x50fc5d,
    FAILED_MODE_NUMBER = 0x50fc7f,
    FAILED_SET_MODE = 0x50fc9f,
    FAILED_COOPERATE_AGAIN = 0x50fcc6,
    FAILED_PRIMARY = 0x50fcec,
    FAILED_BACK = 0x50fd08,
    FAILED_LOCK_BACK = 0x50fd32,
    FAILED_UNLOCK_BACK = 0x50fd9c,
    FAILED_OFFSCREEN = 0x50fdde,
    FAILED_LOCK_OFFSCREEN = 0x50fdfa,
    FAILED_UNLOCK_OFFSCREEN = 0x50fe69
};

/* The modes: 320x200, 640x400, 640x480, 800x600, 1024x768 and 1280x1024 at 8, 16, 24 and 32
 * bits. */
static const uint16_t SIZES[6][2] = {{0x140, 0xc8},  {0x280, 0x190}, {0x280, 0x1e0},
                                     {0x320, 0x258}, {0x400, 0x300}, {0x500, 0x400}};

typedef struct
{
    Port *port;
    uint32_t display, window;
} Video;

/* A COM method of `object`, the object first on the stack. */
static uint32_t method(Video *v, uint32_t object, uint32_t offset, uint32_t eax, uint32_t edx,
                       uint32_t ebx, uint32_t ecx, const uint32_t *rest, unsigned count)
{
    uint32_t stack[6] = {object};
    for (unsigned i = 0; i < count; i++)
    {
        stack[1 + i] = rest[i];
    }
    const uint32_t target = port_u32(v->port, port_u32(v->port, object, 0), offset);
    return port_call_stack(v->port, target, eax, edx, ebx, ecx, stack, count + 1);
}

/* Turns the video off again and reports the failure with its HRESULT. */
static uint32_t fail(Video *v, uint32_t message, uint32_t result)
{
    port_call(v->port, VIDEO_OFF, v->display, v->window, 0, 0);
    port_call(v->port, REPORT, v->display, 1, message, result);
    return port_return(v->port, 0, 0);
}

static uint32_t give_up(Video *v)
{
    port_call(v->port, VIDEO_OFF, v->display, v->window, 0, 0);
    return port_return(v->port, 0, 0);
}

static uint32_t main_window(Port *port)
{
    const uint32_t window = port_u32(port, MAIN_WINDOW, 0);
    return window != 0 ? port_u32(port, window, WINDOW_HWND) : 0;
}

static void clear(Port *port, uint32_t at, uint32_t bytes, uint32_t ecx)
{
    port_call(port, MEMSET, at, 0, bytes, ecx);
}

/* The mode's size and depth, and the sizes the display keeps for it. */
static int set_mode_size(Port *port, uint32_t display, uint32_t mode)
{
    if (mode >= 24)
    {
        return 0;
    }
    port_set16(port, display, DISPLAY_WIDTH, SIZES[mode % 6][0]);
    port_set16(port, display, DISPLAY_HEIGHT, SIZES[mode % 6][1]);
    port_set16(port, display, DISPLAY_DEPTH, 8 * (mode / 6 + 1));
    const uint32_t depth = port_u16(port, display, DISPLAY_DEPTH);
    port_set16(port, display, DISPLAY_PIXEL_BYTES, depth >> 3);
    const uint32_t pixel_bytes = port_u16(port, display, DISPLAY_PIXEL_BYTES);
    const uint32_t bytes = port_u16(port, display, DISPLAY_WIDTH) *
                           port_u16(port, display, DISPLAY_HEIGHT) * pixel_bytes;
    port_set32(port, display, DISPLAY_BYTES, bytes);
    port_set32(port, display, DISPLAY_WORDS, bytes >> 1);
    port_set32(port, display, DISPLAY_DWORDS, bytes >> 2);
    port_set16(port, display, DISPLAY_PITCH, pixel_bytes * port_u16(port, display, DISPLAY_WIDTH));
    const uint32_t pitch = port_u16(port, display, DISPLAY_PITCH);
    port_set16(port, display, DISPLAY_PITCH_WORDS, pitch >> 1);
    port_set16(port, display, DISPLAY_PITCH_DWORDS, pitch >> 2);
    port_set8(port, display, DISPLAY_STATE, 0xd);
    port_set8(port, display, DISPLAY_MODE, mode);
    return 1;
}

/* An image over a locked surface's pixels (0x487280), stored at `global`. */
static void wrap_surface(Port *port, uint32_t display, uint32_t locked, uint32_t global)
{
    const uint32_t image =
        port_call(port, IMAGE_OVER, port_u32(port, locked, DESC_SURFACE),
                  port_u32(port, locked, DESC_WIDTH), port_u32(port, locked, DESC_HEIGHT), 0);
    port_set32(port, global, 0, image);
    port_set8(port, image, 0xd, port_u8(port, display, DISPLAY_IMAGE_BYTE));
    port_set32(port, image, 0x14, port_u32(port, locked, DESC_PITCH));
    port_call(port, IMAGE_PREPARE, image, 0, 0, 0);
}

/* Original 0x484b60. Each DirectDraw method sees in the registers what the original leaves there:
 * mostly the last object, its method table and the last size or flags set. */
uint32_t vertrix_port_video_on_484b60(PORT_SIGNATURE)
{
    uint8_t stack[BELOW + 8];
    Port port;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    const uint32_t frame = entry->esp - 4;
    const uint32_t desc = frame - DESC;
    const uint32_t locked = frame - LOCKED;
    const uint32_t caps = frame - CAPS;
    const uint32_t display = entry->eax;
    const uint32_t mode = entry->ebx & 0xff;
    Video v = {&port, display, entry->edx};

    for (uint32_t k = 0; k < 4; k++)
    {
        port_set32(&port, display, DISPLAY_DDRAW + 4 * k, 0);
    }
    const uint32_t create[4] = {0, display + DISPLAY_DDRAW, IID_IDIRECTDRAW7, 0};
    uint32_t hr = port_call_stack(&port, DIRECTDRAW_CREATE_EX, display + DISPLAY_DDRAW, v.window,
                                  entry->ebx, entry->ecx, create, 4);
    if (hr != 0)
    {
        return fail(&v, FAILED_CREATE, hr);
    }
    uint32_t ddraw = port_u32(&port, display, DISPLAY_DDRAW);
    uint32_t hwnd = main_window(&port);
    uint32_t level[2] = {hwnd, COOPERATIVE};
    hr = method(&v, ddraw, DDRAW_SET_COOPERATIVE_LEVEL, hwnd, ddraw, entry->ebx,
                port_u32(&port, ddraw, 0), level, 2);
    if (hr != 0)
    {
        return fail(&v, FAILED_COOPERATE, hr);
    }
    if (!set_mode_size(&port, display, mode))
    {
        /* The message's argument is the mode, in the low byte of the ecx left 0. */
        return fail(&v, FAILED_MODE_NUMBER, mode);
    }
    const uint32_t width = port_u16(&port, display, DISPLAY_WIDTH);
    const uint32_t size[5] = {width, port_u16(&port, display, DISPLAY_HEIGHT),
                              port_u16(&port, display, DISPLAY_DEPTH), 0, 0};
    hr = method(&v, ddraw, DDRAW_SET_DISPLAY_MODE, ddraw, width, entry->ebx,
                port_u32(&port, ddraw, 0), size, 5);
    if (hr != 0)
    {
        return fail(&v, FAILED_SET_MODE, hr);
    }
    ddraw = port_u32(&port, display, DISPLAY_DDRAW);
    hwnd = main_window(&port);
    level[0] = hwnd;
    hr = method(&v, ddraw, DDRAW_SET_COOPERATIVE_LEVEL, ddraw, hwnd, 0, port_u32(&port, ddraw, 0),
                level, 2);
    if (hr != 0)
    {
        return fail(&v, FAILED_COOPERATE_AGAIN, hr);
    }

    /* The flipping primary surface with one back buffer. */
    clear(&port, desc, SURFACE_DESC_BYTES, FLAGS_CAPS_BACK_BUFFERS);
    port_set32(&port, desc, DESC_FLAGS, FLAGS_CAPS_BACK_BUFFERS);
    port_set32(&port, desc, 0, SURFACE_DESC_BYTES);
    port_set32(&port, desc, DESC_CAPS, CAPS_FLIP_CHAIN);
    port_set32(&port, desc, DESC_BACK_BUFFERS, 1);
    ddraw = port_u32(&port, display, DISPLAY_DDRAW);
    uint32_t created[3] = {desc, display + DISPLAY_PRIMARY, 0};
    hr = method(&v, ddraw, DDRAW_CREATE_SURFACE, ddraw, port_u32(&port, ddraw, 0), CAPS_FLIP_CHAIN,
                desc, created, 3);
    if (hr != 0)
    {
        return fail(&v, FAILED_PRIMARY, hr);
    }
    clear(&port, caps, 0x10, desc);
    port_set32(&port, caps, 0, CAPS_BACK_BUFFER);
    const uint32_t primary = port_u32(&port, display, DISPLAY_PRIMARY);
    const uint32_t attached[2] = {caps, display + DISPLAY_BACK};
    hr = method(&v, primary, SURFACE_GET_ATTACHED, primary, port_u32(&port, primary, 0), 0x10, caps,
                attached, 2);
    if (hr != 0 || port_u32(&port, display, DISPLAY_BACK) == 0)
    {
        return fail(&v, FAILED_BACK, hr);
    }

    /* Lock the back buffer to learn its pixels and format. */
    clear(&port, locked, SURFACE_DESC_BYTES, caps);
    port_set32(&port, locked, 0, SURFACE_DESC_BYTES);
    const uint32_t back = port_u32(&port, display, DISPLAY_BACK);
    const uint32_t lock[4] = {0, locked, DDLOCK_WAIT, 0};
    hr = method(&v, back, SURFACE_LOCK, back, port_u32(&port, back, 0), SURFACE_DESC_BYTES, locked,
                lock, 4);
    if (hr != 0)
    {
        return fail(&v, FAILED_LOCK_BACK, hr);
    }
    if (port_u32(&port, locked, DESC_SURFACE) == 0)
    {
        return give_up(&v);
    }
    const uint32_t depth = port_u16(&port, display, DISPLAY_DEPTH);
    if (depth == 8)
    {
        /* 3-3-2 for the palette's colours. */
        port_set32(&port, display, DISPLAY_RED, 0xe0);
        port_set32(&port, display, DISPLAY_GREEN, 0x1c);
        port_set32(&port, display, DISPLAY_BLUE, 3);
        port_set32(&port, display, DISPLAY_ALPHA, 0);
    }
    else
    {
        for (uint32_t k = 0; k < 4; k++)
        {
            port_set32(&port, display, 4 * k, port_u32(&port, locked, DESC_RED_MASK + 4 * k));
        }
        if (depth == 32)
        {
            port_set32(&port, display, DISPLAY_ALPHA, 0xff000000u);
        }
    }
    const uint32_t blue = port_u32(&port, display, DISPLAY_BLUE);
    const uint32_t alpha = port_u32(&port, display, DISPLAY_ALPHA);
    if (port_call_stack(&port, SET_FORMAT, display + DISPLAY_FORMAT,
                        port_u32(&port, display, DISPLAY_RED),
                        port_u32(&port, display, DISPLAY_GREEN), blue, &alpha, 1) == 0)
    {
        return give_up(&v);
    }
    wrap_surface(&port, display, locked, BACK_IMAGE);
    port_call(&port, IMAGE_NAME, port_u32(&port, BACK_IMAGE, 0), BACK_NAME, 0, 0);
    const uint32_t height = port_u32(&port, locked, DESC_HEIGHT);
    const uint32_t unlock[1] = {0};
    const uint32_t back_again = port_u32(&port, display, DISPLAY_BACK);
    hr = method(&v, back_again, SURFACE_UNLOCK, back_again, port_u32(&port, back_again, 0), height,
                blue, unlock, 1);
    if (hr != 0)
    {
        return fail(&v, FAILED_UNLOCK_BACK, hr);
    }
    port_set32(&port, display, DISPLAY_IN_VIDEO_MEMORY,
               (port_u8(&port, locked, DESC_CAPS + 1) & CAPS_VIDEO_MEMORY_BYTE) != 0);
    if (port_u16(&port, display, DISPLAY_DEPTH) == 8)
    {
        port_call(&port, PALETTE_CLEAR, PALETTE, 0, PALETTE_BYTES, blue);
        port_call(&port, MEMSET, PALETTE_SAVED, 0, PALETTE_BYTES, blue);
        port_call(&port, PALETTE_APPLY, PALETTE, 0, PALETTE_BYTES, blue);
        port_call(&port, PALETTE_ATTACH_DDRAW, v.window, port_u32(&port, display, DISPLAY_DDRAW),
                  PALETTE_BYTES, blue);
        port_call(&port, PALETTE_ATTACH_PRIMARY, v.window,
                  port_u32(&port, display, DISPLAY_PRIMARY), PALETTE_BYTES, blue);
    }

    /* The offscreen surface, in video memory when there is room, else in system memory. */
    const uint32_t offscreen_slot = display + DISPLAY_OFFSCREEN;
    clear(&port, desc, SURFACE_DESC_BYTES, SURFACE_DESC_BYTES);
    port_set32(&port, desc, 0, SURFACE_DESC_BYTES);
    port_set32(&port, desc, DESC_FLAGS, FLAGS_SIZED);
    port_set32(&port, desc, DESC_CAPS, CAPS_OFFSCREEN_VIDEO);
    port_set32(&port, desc, DESC_HEIGHT, port_u16(&port, display, DISPLAY_HEIGHT));
    port_set32(&port, desc, DESC_WIDTH, port_u16(&port, display, DISPLAY_WIDTH));
    ddraw = port_u32(&port, display, DISPLAY_DDRAW);
    created[1] = offscreen_slot;
    hr = method(&v, ddraw, DDRAW_CREATE_SURFACE, ddraw, port_u32(&port, ddraw, 0), FLAGS_SIZED,
                desc, created, 3);
    uint32_t ecx = desc;
    if (hr == DDERR_OUTOFVIDEOMEMORY)
    {
        clear(&port, desc, SURFACE_DESC_BYTES, desc);
        port_set32(&port, desc, 0, SURFACE_DESC_BYTES);
        port_set32(&port, desc, DESC_FLAGS, FLAGS_SIZED);
        port_set32(&port, desc, DESC_CAPS, CAPS_OFFSCREEN_SYSTEM);
        port_set32(&port, desc, DESC_HEIGHT, port_u16(&port, display, DISPLAY_HEIGHT));
        port_set32(&port, desc, DESC_WIDTH, port_u16(&port, display, DISPLAY_WIDTH));
        ddraw = port_u32(&port, display, DISPLAY_DDRAW);
        ecx = port_u32(&port, ddraw, 0);
        hr = method(&v, ddraw, DDRAW_CREATE_SURFACE, ddraw, desc, offscreen_slot, ecx, created, 3);
    }
    if (hr != 0)
    {
        return fail(&v, FAILED_OFFSCREEN, hr);
    }
    clear(&port, locked, SURFACE_DESC_BYTES, ecx);
    port_set32(&port, locked, 0, SURFACE_DESC_BYTES);
    const uint32_t offscreen = port_u32(&port, offscreen_slot, 0);
    hr = method(&v, offscreen, SURFACE_LOCK, offscreen, locked, SURFACE_DESC_BYTES,
                port_u32(&port, offscreen, 0), lock, 4);
    if (hr != 0)
    {
        return fail(&v, FAILED_LOCK_OFFSCREEN, hr);
    }
    if (port_u32(&port, locked, DESC_SURFACE) == 0)
    {
        return give_up(&v);
    }
    wrap_surface(&port, display, locked, OFFSCREEN_IMAGE);
    const uint32_t image_again = port_u32(&port, OFFSCREEN_IMAGE, 0);
    port_set32(&port, image_again, 0, port_u32(&port, locked, DESC_SURFACE));
    port_call(&port, IMAGE_NAME, image_again, OFFSCREEN_NAME, 0, 0);
    const uint32_t offscreen_again = port_u32(&port, offscreen_slot, 0);
    hr = method(&v, offscreen_again, SURFACE_UNLOCK, offscreen_again,
                port_u32(&port, offscreen_again, 0), port_u32(&port, locked, DESC_HEIGHT),
                image_again, unlock, 1);
    if (hr != 0)
    {
        return fail(&v, FAILED_UNLOCK_OFFSCREEN, hr);
    }
    return port_return(&port, 1, 0);
}
