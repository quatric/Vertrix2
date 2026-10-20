/* The original's own code on the Wii: the lifted startup, loader, banks and frame loop run
 * through the dispatcher on the platform host (lift_host.c), the data comes from the original
 * archive on the SD card, and the DirectDraw back buffer is presented as the display frame.
 * The original's mapped image is linked in (build/image.bin, from tools/dump_image.py). */
#include <asndlib.h>
#include <gccore.h>
#include <ogc/lwp_watchdog.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/iosupport.h>
#include <wiiuse/wpad.h>

#include "input_wii.h"
#include "wiiupdate.h"

#include "jpeg_decode.h"
#include "lift_host.h"
#include "wii_archive.h"
#include "wii_audio.h"
#include "wii_frame_texture.h"
#include "wii_video.h"

extern const uint8_t image_bin[];

enum
{
    WIDTH = 640,
    HEIGHT = 480,
    HEAP_RESERVE = 1024 * 1024, /* left in MEM2 for the libraries */
    /* Lifted frames are C locals (up to 0x4000 bytes, 16 deep) and the native ports nest between
     * them; the main thread's 128 KB stack overflowed once the MP3 setup ran. */
    GAME_STACK = 2 * 1024 * 1024,
    FRAME_MS = 33
};

static uint8_t image[LIFT_HOST_IMAGE_SIZE];
static VertrixWiiVideo video;
static VertrixWiiArchive archive;
static VertrixWiiTexture texture;
static uint8_t pixels[WIDTH * HEIGHT * 4];

static void host_store(LiftHost *host, uint32_t address, uint32_t value)
{
    lift_host_write32(host, address, value);
}

/* Console output is also written to sd:/apps/vertrix2/log.txt, so the last lines before an exit
 * to the menu can be read afterwards. */
static FILE *log_file;
static const devoptab_t *console_out;
static devoptab_t tee_out;

/* libogc's SYS_STDIO_Report writer turns the line ends into carriage returns in the buffer it is
 * given, before it looks for a UART. newlib hands it string constants directly (puts' "\n", which
 * the linker shares with every constant ending in a newline: libwiiupdate's HTTP request among
 * them, which GitHub then refused), so it only ever sees a copy. */
static ssize_t tee_write(struct _reent *r, void *fd, const char *data, size_t length)
{
    char copy[256];
    size_t done;
    if (log_file != NULL)
    {
        fwrite(data, 1, length, log_file);
        fflush(log_file);
    }
    for (done = 0; done < length;)
    {
        size_t n = length - done < sizeof copy ? length - done : sizeof copy;
        memcpy(copy, data + done, n);
        console_out->write_r(r, fd, copy, n);
        done += n;
    }
    return (ssize_t)length;
}

static void report_stdio(void)
{
    SYS_STDIO_Report(true);
    console_out = devoptab_list[STD_OUT];
    tee_out = *console_out;
    tee_out.write_r = tee_write;
    devoptab_list[STD_OUT] = &tee_out;
    devoptab_list[STD_ERR] = &tee_out;
}

/* The original's wave-out blocks go to ASND voice 0 as they are written. */
static void wave_output(void *context, const uint8_t *samples, uint32_t bytes, uint32_t rate,
                        uint32_t channels, uint32_t bits)
{
    (void)context;
    vertrix_wii_stream_write(0, samples, bytes, rate, channels, bits);
}

static void log_to_sd(void)
{
    log_file = fopen("sd:/apps/vertrix2/log.txt", "w");
}

static void fail(const char *message)
{
    CON_InitEx(&video.mode, 20, 20, video.mode.fbWidth - 40, video.mode.xfbHeight - 40);
    printf("Vertrix2\n\n%s\n\nHOME exits.\n", message);
    for (;;)
    {
        INPUT_Update();
        if (INPUT_PadsDown() & WPAD_BUTTON_HOME)
        {
            exit(1);
        }
        VIDEO_WaitVSync();
    }
}

/* The back buffer is little-endian x86 memory (bytes B, G, R, unused); the frame texture reads
 * the bytes in that order with the masks below, so copy the bytes and make the unused one opaque.
 */
/* The frame to upload: the back buffer itself when it lies in one heap block (the frame draw
 * ignores the unused fourth byte), else a copy gathered pixel by pixel. */
static uint8_t *gather(const LiftHost *host, uint32_t base)
{
    const uint8_t *frame = lift_host_bytes(host, base, WIDTH * HEIGHT * 4);
    unsigned i;
    if (frame != NULL)
    {
        return (uint8_t *)frame;
    }
    for (i = 0; i < WIDTH * HEIGHT; i++)
    {
        uint32_t value = lift_host_read(host, base + 4 * i, 4);
        pixels[4 * i + 0] = (uint8_t)value;
        pixels[4 * i + 1] = (uint8_t)(value >> 8);
        pixels[4 * i + 2] = (uint8_t)(value >> 16);
        pixels[4 * i + 3] = 0xff;
    }
    return pixels;
}

/* The original reads a DirectInput keyboard and mouse. The controllers' buttons become keys: the
 * D-pad (or a stick) the arrow keys, A Enter, B Space, 1 and 2 Z and X, minus Escape; A also
 * presses the mouse button, so the pointer clicks with it. */
static const struct
{
    uint32_t button;
    unsigned scan_code;
} pad_keys[] = {{WPAD_BUTTON_UP, 0xc8},    {WPAD_BUTTON_DOWN, 0xd0}, {WPAD_BUTTON_LEFT, 0xcb},
                {WPAD_BUTTON_RIGHT, 0xcd}, {WPAD_BUTTON_A, 0x1c},    {WPAD_BUTTON_B, 0x39},
                {WPAD_BUTTON_1, 0x2c},     {WPAD_BUTTON_2, 0x2d},    {WPAD_BUTTON_MINUS, 0x01}};

/* A USB keyboard is the original's keyboard: USB HID usage codes to DirectInput scan codes. */
static const uint8_t usb_scan_codes[0xe8] = {
    [0x04] = 0x1e, [0x05] = 0x30, [0x06] = 0x2e, [0x07] = 0x20, [0x08] = 0x12, [0x09] = 0x21,
    [0x0a] = 0x22, [0x0b] = 0x23, [0x0c] = 0x17, [0x0d] = 0x24, [0x0e] = 0x25, [0x0f] = 0x26,
    [0x10] = 0x32, [0x11] = 0x31, [0x12] = 0x18, [0x13] = 0x19, [0x14] = 0x10, [0x15] = 0x13,
    [0x16] = 0x1f, [0x17] = 0x14, [0x18] = 0x16, [0x19] = 0x2f, [0x1a] = 0x11, [0x1b] = 0x2d,
    [0x1c] = 0x15, [0x1d] = 0x2c, [0x1e] = 0x02, [0x1f] = 0x03, [0x20] = 0x04, [0x21] = 0x05,
    [0x22] = 0x06, [0x23] = 0x07, [0x24] = 0x08, [0x25] = 0x09, [0x26] = 0x0a, [0x27] = 0x0b,
    [0x28] = 0x1c, [0x29] = 0x01, [0x2a] = 0x0e, [0x2b] = 0x0f, [0x2c] = 0x39, [0x2d] = 0x0c,
    [0x2e] = 0x0d, [0x2f] = 0x1a, [0x30] = 0x1b, [0x31] = 0x2b, [0x33] = 0x27, [0x34] = 0x28,
    [0x35] = 0x29, [0x36] = 0x33, [0x37] = 0x34, [0x38] = 0x35, [0x39] = 0x3a, [0x3a] = 0x3b,
    [0x3b] = 0x3c, [0x3c] = 0x3d, [0x3d] = 0x3e, [0x3e] = 0x3f, [0x3f] = 0x40, [0x40] = 0x41,
    [0x41] = 0x42, [0x42] = 0x43, [0x43] = 0x44, [0x44] = 0x57, [0x45] = 0x58, [0x48] = 0xc5,
    [0x49] = 0xd2, [0x4a] = 0xc7, [0x4b] = 0xc9, [0x4c] = 0xd3, [0x4d] = 0xcf, [0x4e] = 0xd1,
    [0x4f] = 0xcd, [0x50] = 0xcb, [0x51] = 0xd0, [0x52] = 0xc8, [0x58] = 0x9c, [0xe0] = 0x1d,
    [0xe1] = 0x2a, [0xe2] = 0x38, [0xe4] = 0x9d, [0xe5] = 0x36, [0xe6] = 0xb8};

/* The strongest stick (Nunchuk, Classic, GameCube) past half way acts as the D-pad. */
static uint32_t stick_directions(void)
{
    float x, y;
    uint32_t held = 0;
    if (INPUT_Stick(INPUT_STICK_LEFT, &x, &y, NULL) > 0.5f)
    {
        held |= x < -0.5f ? WPAD_BUTTON_LEFT : x > 0.5f ? WPAD_BUTTON_RIGHT : 0;
        held |= y < -0.5f ? WPAD_BUTTON_DOWN : y > 0.5f ? WPAD_BUTTON_UP : 0;
    }
    return held;
}

static void pad_events(LiftHost *host, uint32_t held)
{
    static uint32_t before;
    uint32_t down = held & ~before, up = before & ~held;
    unsigned k;
    before = held;
    for (k = 0; k < sizeof pad_keys / sizeof pad_keys[0]; k++)
    {
        if (down & pad_keys[k].button)
        {
            lift_host_key(host, pad_keys[k].scan_code, 1);
        }
        if (up & pad_keys[k].button)
        {
            lift_host_key(host, pad_keys[k].scan_code, 0);
        }
    }
    if (down & WPAD_BUTTON_A)
    {
        lift_host_mouse(host, 12, 0x80);
    }
    if (up & WPAD_BUTTON_A)
    {
        lift_host_mouse(host, 12, 0);
    }
}

static void keyboard_events(LiftHost *host)
{
    unsigned code;
    for (code = 0; code < sizeof usb_scan_codes; code++)
    {
        if (usb_scan_codes[code] != 0 && INPUT_KeyPressed((u8)code))
        {
            lift_host_key(host, usb_scan_codes[code], 1);
        }
        if (usb_scan_codes[code] != 0 && INPUT_KeyReleased((u8)code))
        {
            lift_host_key(host, usb_scan_codes[code], 0);
        }
    }
}

/* The remote's pointer or a USB mouse is the original's mouse: the position goes straight into
 * the mouse object (x, y words at +0x48), and a motion event makes the poll publish it. */
static void pointer_events(LiftHost *host)
{
    u8 pressed = INPUT_MouseButtonsPressed(), released = INPUT_MouseButtonsReleased();
#ifndef VERTRIX_AUTOPLAY
    /* the scripted walk places the pointer in unattended runs; an emulator's idle IR must not */
    if (INPUT_CursorActive() && INPUT_CursorMoved())
    {
        int x, y;
        INPUT_CursorPosition(&x, &y);
        host_store(host, 0x5588f8 + 0x48, (uint32_t)x | ((uint32_t)y << 16));
        lift_host_mouse(host, 0, 0);
    }
#endif
    if (pressed & INPUT_MOUSE_LEFT)
    {
        lift_host_mouse(host, 12, 0x80);
    }
    if (released & INPUT_MOUSE_LEFT)
    {
        lift_host_mouse(host, 12, 0);
    }
    if (pressed & INPUT_MOUSE_RIGHT)
    {
        lift_host_mouse(host, 13, 0x80);
    }
    if (released & INPUT_MOUSE_RIGHT)
    {
        lift_host_mouse(host, 13, 0);
    }
}

/* The update check (libwiiupdate) runs on its own thread below the game's priority; its popup is
 * drawn over the frame only while it is open. */
static wiiupdate_popup popup;
static int popup_state, popup_dirty;

static int update_popup(uint32_t down)
{
    wiiupdate_popup before = popup;
    int state = WIIUPDATE_Popup(down, &popup);
    if (state != popup_state ||
        (state == WIIUPDATE_POPUP_OPEN && memcmp(&before, &popup, sizeof popup) != 0))
    {
        popup_dirty = 1;
    }
    popup_state = state;
    return state;
}

extern const uint8_t console_font_8x16[];

static void fill(uint8_t *frame, int x0, int y0, int w, int h, uint32_t bgr)
{
    int x, y;
    for (y = y0; y < y0 + h; y++)
    {
        uint8_t *p = frame + 4 * (y * WIDTH + x0);
        for (x = 0; x < w; x++, p += 4)
        {
            p[0] = (uint8_t)bgr;
            p[1] = (uint8_t)(bgr >> 8);
            p[2] = (uint8_t)(bgr >> 16);
        }
    }
}

/* Text in libogc's console font; returns the characters drawn. */
static int text(uint8_t *frame, int x, int y, const char *s, int max, uint32_t bgr)
{
    int n = 0;
    for (; s[n] != '\0' && n < max; n++)
    {
        const uint8_t *glyph = console_font_8x16 + 16 * (uint8_t)s[n];
        int row, col;
        for (row = 0; row < 16; row++)
        {
            for (col = 0; col < 8; col++)
            {
                if (glyph[row] & (0x80 >> col))
                {
                    fill(frame, x + 8 * n + col, y + row, 1, 1, bgr);
                }
            }
        }
    }
    return n;
}

static uint8_t *draw_popup(uint8_t *frame)
{
    enum
    {
        BOX_X = 40,
        BOX_Y = 150,
        BOX_W = WIDTH - 80,
        BOX_H = 180,
        COLUMNS = (BOX_W - 32) / 8
    };
    const char *line = popup.text;
    int y = BOX_Y + 52;
    if (frame != pixels)
    {
        memcpy(pixels, frame, sizeof pixels); /* the back buffer itself stays the original's */
    }
    fill(pixels, BOX_X - 2, BOX_Y - 2, BOX_W + 4, BOX_H + 4, 0xc0c0c0);
    fill(pixels, BOX_X, BOX_Y, BOX_W, BOX_H, 0x202020);
    text(pixels, BOX_X + 16, BOX_Y + 16, popup.title, COLUMNS, 0xffff60);
    while (*line != '\0' && y < BOX_Y + 52 + 3 * 18)
    {
        int n = (int)strlen(line) > COLUMNS ? COLUMNS : (int)strlen(line);
        if (line[n] != '\0')
        {
            while (n > 0 && line[n] != ' ')
            {
                n--; /* wrap at a space */
            }
            n = n > 0 ? n : COLUMNS;
        }
        text(pixels, BOX_X + 16, y, line, n, 0xffffff);
        line += n;
        line += *line == ' ';
        y += 18;
    }
    text(pixels, BOX_X + 16, BOX_Y + 112, popup.detail, COLUMNS, 0xa0a0a0);
    if (popup.progress >= 0)
    {
        fill(pixels, BOX_X + 16, BOX_Y + 132, BOX_W - 32, 12, 0x404040);
        fill(pixels, BOX_X + 16, BOX_Y + 132, (BOX_W - 32) * popup.progress / 100, 12, 0x40c040);
    }
    text(pixels, BOX_X + 16, BOX_Y + 152, popup.hint, COLUMNS, 0xffffff);
    return pixels;
}

/* Below the update thread while it has work that matters (the check, or the popup's download),
 * above it otherwise; the check mostly waits on the network and finishes during the load. */
static void game_priority(void)
{
    static int low = 1, checked = WIIUPDATE_CHECKING;
    wiiupdate_state state = WIIUPDATE_State();
    int want = state == WIIUPDATE_CHECKING || popup_state == WIIUPDATE_POPUP_OPEN;
    if ((int)state != checked)
    {
        checked = (int)state;
        printf("update check: state %d, latest \"%s\"\n", checked, WIIUPDATE_Latest());
    }
    if (want != low)
    {
        low = want;
        LWP_SetThreadPriority(LWP_GetSelf(), low ? 30 : 64);
    }
}

static void *game_main(void *unused)
{
    const uint32_t masks[3] = {0x00ff0000, 0x0000ff00, 0x000000ff};
    VertrixSurface frame = {pixels, sizeof pixels, WIDTH, HEIGHT, WIDTH * 4, 4};
    static LiftHost host;
    uint8_t *heap;
    uint32_t heap_size;
    int lifted;
    uint32_t form, display, base, width, height, pitch, bytes, start;
    unsigned shown = 0;
    uint32_t polled = 0, pads, pads_down;
    (void)unused;
    if (!vertrix_wii_video_init(&video))
    {
        return NULL;
    }
    INPUT_Init();
    INPUT_SetScreenSize(WIDTH, HEIGHT);
    /* The USB keyboard's own presses go to the original as keys (keyboard_events), so it does not
     * also act as a controller. */
    INPUT_KeyboardMapClear();
    report_stdio();
    if (vertrix_wii_archive_open(&archive) != VERTRIX_WII_ARCHIVE_OK)
    {
        fail("Could not read sd:/apps/vertrix2/Vertrix2.vf.");
    }
    log_to_sd();
    heap = (uint8_t *)SYS_GetArena2Lo();
    heap_size = (uint32_t)SYS_GetArena2Hi() - (uint32_t)heap;
    if (heap_size < 48u * 1024 * 1024 + HEAP_RESERVE)
    {
        fail("Not enough memory for the original's heap.");
    }
    heap_size -= HEAP_RESERVE;
    printf("original heap: %u bytes\n", (unsigned)heap_size);
    SYS_SetArena2Lo(heap + heap_size);
    printf("starting\n");
    lift_host_init(&host, image, image_bin, heap, heap_size);
    {
        /* The large buffers (the 640x480 surfaces) go to what is left of MEM1. */
        uint8_t *low = (uint8_t *)(((uint32_t)SYS_GetArena1Lo() + 31u) & ~31u);
        int32_t room = (int32_t)((uint32_t)SYS_GetArena1Hi() - (uint32_t)low) - 4 * 1024 * 1024;
        if (room > 0)
        {
            printf("second heap: %d bytes in MEM1\n", (int)room);
            SYS_SetArena1Lo(low + room);
            lift_host_set_heap2(&host, low, (uint32_t)room);
        }
    }
    /* The update check's thread runs at priority 40 and the game at 64, which never waits while it
     * is behind on frames, so the check would never finish: the game steps below it while it
     * loads (no frames to drop) and goes back up once the check is done (game_priority). */
    WIIUPDATE_Start("quatric", "Vertrix2", APP_VERSION);
    LWP_SetThreadPriority(LWP_GetSelf(), 30);
    host.archive = archive.archive;
    host.decode_jpeg = jpeg_decode;
    ASND_Init();
    ASND_Pause(0);
    host.wave_output = wave_output;
    form = lift_host_allocate(&host, 0x1000);
    display = lift_host_allocate(&host, 0x800);
    host_store(&host, 0x544070, display);
    lift_host_startup(&host, &lifted);
    lift_host_run(&host, 0x41a080, form, 0, 0, 0, &lifted); /* master startup */
    printf("done master startup at %u ms\n", (unsigned)ticks_to_millisecs(gettime()));
    lift_host_run(&host, 0x41a540, form, 0, 0, 0, &lifted); /* loader */
    printf("done loader at %u ms\n", (unsigned)ticks_to_millisecs(gettime()));
    lift_host_run(&host, 0x45dca0, 0, 0, 0, 0, &lifted); /* sprite banks */
    printf("done sprite banks at %u ms\n", (unsigned)ticks_to_millisecs(gettime()));
    lift_host_run(&host, 0x45dca0, 0, 0, 0, 0, &lifted); /* sprite banks */
    printf("done sprite banks at %u ms\n", (unsigned)ticks_to_millisecs(gettime()));
    base = lift_host_surface(&host, host.primary_surface, &width, &height, &pitch, &bytes);
    frame.data = gather(&host, base);
    if (!vertrix_wii_frame_texture_init(&frame, masks, GX_NEAR, &texture))
    {
        fail("Could not upload the display frame.");
    }
    printf("lifted game running\n");
    start = ticks_to_millisecs(gettime());
    for (;;)
    {
        /* The original's idle handler chain: the form's current handler runs one step per tick
         * and installs the next one (0x418840 stores it at +0xbc). */
        uint32_t handler = lift_host_read(&host, form + 0xbc, 4), before = host.frames_presented;
        uint32_t tick = ticks_to_millisecs(gettime());
        if (tick - polled >= 4)
        {
            /* Every controller, keyboard and mouse through libwiiinput, read at most every 4 ms:
             * the remote reports at 100-200 Hz and the loop turns far faster than that. */
            polled = tick;
            INPUT_Update();
            pads = INPUT_PadsHeld() | stick_directions();
            pads_down = INPUT_PadsDown();
            if (update_popup(pads_down) == WIIUPDATE_POPUP_OPEN)
            {
                pads = 0; /* the popup has the buttons: let go of everything the game holds */
            }
            if (pads_down & WPAD_BUTTON_HOME)
            {
                printf("HOME pressed at %u ms\n", (unsigned)(tick - start));
                break;
            }
            if (popup_state == WIIUPDATE_POPUP_EXIT)
            {
                printf("update installed at %u ms\n", (unsigned)(tick - start));
                break;
            }
            game_priority();
            pad_events(&host, pads);
            if (popup_state != WIIUPDATE_POPUP_OPEN)
            {
                keyboard_events(&host);
                pointer_events(&host);
            }
        }
        {
#ifdef VERTRIX_AUTOPLAY
            {
                /* Scripted pointer for unattended runs: the same walk through the menus the host
                 * tool makes (main menu, players selection, ready to fight, yes). */
                static unsigned n;
                static int started;
                static unsigned last_n;
                static const struct
                {
                    unsigned at;
                    int x, y;
                } moves[] = {{150, 320, 350}, {190, 320, 402}, {230, 320, 402}, {320, 330, 130},
                             {360, 330, 130}, {400, 415, 445}, {440, 415, 445}, {480, 415, 445}};
                unsigned m, ph;
                if (handler == 0x41b820)
                {
                    started = 1;
                }
                static uint32_t menu_ms;
                if (started && menu_ms == 0)
                {
                    menu_ms = tick;
                }
                /* the host tool steps the clock 120 ms per tick and its menu first runs at tick 89
                 */
                n = started ? 89 + (tick - menu_ms) / 120 : 89;
                ph = n >= 150 ? (n - 150) % 40 : 0;
                if (handler == 0x41c7b0 || handler == 0x41d0e0)
                {
                    /* players selection: the GO preview; ready to fight: YES */
                    host_store(&host, 0x5588f8 + 0x48,
                               handler == 0x41c7b0 ? (330u | (130u << 16)) : (415u | (445u << 16)));
                }
                for (m = 0; m < sizeof moves / sizeof moves[0] && handler == 0x41b820; m++)
                {
                    if (moves[m].at <= n && moves[m].at > last_n)
                    {
                        host_store(&host, 0x5588f8 + 0x48,
                                   (uint32_t)moves[m].x | ((uint32_t)moves[m].y << 16));
                        printf("autoplay move %d %d at n %u\n", moves[m].x, moves[m].y, n);
                    }
                }
                {
                    static int pressed;
                    if (n >= 150 && ph >= 2 && ph < 25 && !pressed)
                    {
                        lift_host_mouse(&host, 12, 0x80);
                        pressed = 1;
                        printf("autoplay press at n %u, screen %u\n", n,
                               (unsigned)lift_host_read(&host, 0x532a4c, 4));
                        printf("  mouse pos %u,%u raw %x flag553648 %x\n",
                               (unsigned)lift_host_read(&host, 0x5588f8 + 0x48, 2),
                               (unsigned)lift_host_read(&host, 0x5588f8 + 0x4a, 2),
                               (unsigned)lift_host_read(&host, 0x558944, 4),
                               (unsigned)lift_host_read(&host, 0x553648, 4));
                    }
                    if (n >= 150 && (ph >= 25 || ph < 2) && pressed)
                    {
                        lift_host_mouse(&host, 12, 0);
                        pressed = 0;
                    }
                }
                if (n >= 150 && n <= 160 && n != last_n)
                {
                    printf("  slot state %x list %x,%x,%x pending %u/%u\n",
                           (unsigned)lift_host_read(&host, 0x5501c4, 1),
                           (unsigned)lift_host_read(&host, 0x5501e4, 4),
                           (unsigned)lift_host_read(&host, 0x5501e8, 4),
                           (unsigned)lift_host_read(&host, 0x5501ec, 4), host.mouse_head,
                           host.mouse_tail);
                }
                if (started)
                {
                    lift_host_mouse(&host, 0, 0);
                }
                if (started && n != last_n && (n == 156 || n == 170 || n == 200))
                {
                    uint32_t cnt = lift_host_read(&host, 0x546724, 4),
                             arr = lift_host_read(&host, 0x546720, 4), q;
                    printf("  actors %u mouse %u,%u hover %x:", (unsigned)cnt,
                           (unsigned)lift_host_read(&host, 0x5588f8 + 0x48, 2),
                           (unsigned)lift_host_read(&host, 0x5588f8 + 0x4a, 2),
                           (unsigned)lift_host_read(&host, 0x558944, 4));
                    for (q = 0; q < cnt && q < 12; q++)
                    {
                        uint32_t a = lift_host_read(&host, arr + 4 * q, 4);
                        printf(" [t%x h%x]", (unsigned)lift_host_read(&host, a + 0x14c, 4),
                               (unsigned)lift_host_read(&host, a + 0x154, 4));
                    }
                    printf("\n");
                    {
                        uint32_t a0 = lift_host_read(&host, arr + 12, 4), o;
                        printf("  fields %x:", (unsigned)a0);
                        for (o = 0; o < 0x160; o += 4)
                        {
                            uint32_t v = lift_host_read(&host, a0 + o, 4);
                            if (v && v < 0x3000000)
                            {
                                printf(" %x:%x", (unsigned)o, (unsigned)v);
                            }
                        }
                        printf("\n");
                    }
                }
                last_n = n;
            }
#endif
            host_store(&host, 0x5328bc, 1); /* the form is active: the device poll may run */
            lift_host_run(&host, 0x4b7b80, 0, 0, 0, 0,
                          &lifted); /* the 14 ms timer: polls the devices */
        }
        {
            static unsigned loops;
            if (++loops % 5000 == 0)
            {
                printf("loop %u at %u ms, handler %x, %u frames\n", loops, (unsigned)(tick - start),
                       (unsigned)handler, (unsigned)host.frames_presented);
            }
        }
        host.clock_ms = tick - start;
        lift_host_thread_step(&host, &lifted);
        lifted = 1;
        if (handler != 0)
        {
            lift_host_run(&host, handler, form, 0, 0, 0, &lifted);
        }
        {
            static uint32_t last_handler, changes;
            if (handler != last_handler && changes < 200)
            {
                last_handler = handler;
                changes++;
                printf("handler -> %x at %u ms\n", (unsigned)handler, (unsigned)(tick - start));
            }
        }
        if (!lifted)
        {
            printf("handler %x is not lifted\n", (unsigned)handler);
            fail("The original asked for a routine that is not lifted yet.");
        }
        if (host.close_requested)
        {
            printf("EXIT: the original closed its window\n");
            break; /* return to the loader */
        }
        if (host.frames_presented != before || popup_dirty)
        {
            base = lift_host_surface(&host, host.primary_surface, &width, &height, &pitch, &bytes);
            frame.data = gather(&host, base);
            if (popup_state == WIIUPDATE_POPUP_OPEN)
            {
                frame.data = draw_popup(frame.data);
            }
            popup_dirty = 0;
            if (shown < 5)
            {
                printf("frame %u: handler %x, %u ms\n", shown++, (unsigned)handler,
                       (unsigned)(ticks_to_millisecs(gettime()) - tick));
            }
#ifdef VERTRIX_AUTOPLAY
            if (handler == 0x424990)
            {
                static unsigned gameplay_frames;
                static uint32_t play_ms;
                if (++gameplay_frames == 1)
                {
                    play_ms = tick;
                }
                if (gameplay_frames == 600)
                {
                    printf("600 gameplay frames in %u ms\n", (unsigned)(tick - play_ms));
                    FILE *shot = fopen("sd:/apps/vertrix2/shot.ppm", "wb");
                    if (shot != NULL)
                    {
                        unsigned i;
                        fprintf(shot, "P6\n%d %d\n255\n", WIDTH, HEIGHT);
                        for (i = 0; i < WIDTH * HEIGHT; i++)
                        {
                            fputc(frame.data[4 * i + 2], shot);
                            fputc(frame.data[4 * i + 1], shot);
                            fputc(frame.data[4 * i + 0], shot);
                        }
                        fclose(shot);
                        printf("screenshot written\n");
                        exit(0);
                    }
                    else
                    {
                        printf("screenshot file could not be opened\n");
                    }
                }
            }
#endif
            if (!vertrix_wii_frame_texture_update(&frame, masks, &texture))
            {
                fail("Could not update the frame texture.");
            }
            if (!vertrix_wii_frame_present(&video.presenter, &texture))
            {
                fail("Could not present the frame.");
            }
        }
    }
    vertrix_wii_texture_free(&texture);
    vertrix_wii_archive_close(&archive);
    return NULL;
}

int main(int argc, char **argv)
{
    /* The game's stack comes from MEM2, ahead of the original's heap: MEM1 is kept for the large
     * surfaces (the second heap). */
    uint8_t *stack = (uint8_t *)(((uint32_t)SYS_GetArena2Lo() + 31u) & ~31u);
    lwp_t thread;
    SYS_SetArena2Lo(stack + GAME_STACK);
    WIIUPDATE_SetAppPath(argc > 0 ? argv[0] : NULL);
    if (LWP_CreateThread(&thread, game_main, NULL, stack, GAME_STACK, 64) != 0)
    {
        return 1;
    }
    LWP_JoinThread(thread, NULL);
    return 0;
}
