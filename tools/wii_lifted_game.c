/* The original's own code on the Wii: the lifted startup, loader, banks and frame loop run
 * through the dispatcher on the platform host (lift_host.c), the data comes from the original
 * archive on the SD card, and the DirectDraw back buffer is presented as the display frame.
 * The original's mapped image is linked in (build/image.bin, from tools/dump_image.py). */
#include <gccore.h>
#include <ogc/lwp_watchdog.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wiiuse/wpad.h>

#include "jpeg_decode.h"
#include "lift_host.h"
#include "wii_archive.h"
#include "wii_frame_texture.h"
#include "wii_video.h"

extern const uint8_t image_bin[];

enum
{
    WIDTH = 640,
    HEIGHT = 480,
    HEAP_RESERVE = 1024 * 1024, /* left in MEM2 for the libraries */
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

static void fail(const char *message)
{
    CON_InitEx(&video.mode, 20, 20, video.mode.fbWidth - 40, video.mode.xfbHeight - 40);
    printf("Vertrix2\n\n%s\n\nHOME exits.\n", message);
    for (;;)
    {
        WPAD_ScanPads();
        if (WPAD_ButtonsDown(0) & WPAD_BUTTON_HOME)
        {
            exit(1);
        }
        VIDEO_WaitVSync();
    }
}

/* The back buffer is little-endian x86 memory (bytes B, G, R, unused); the frame texture reads
 * the bytes in that order with the masks below, so copy the bytes and make the unused one opaque.
 */
static void gather(const LiftHost *host, uint32_t base)
{
    unsigned i;
    for (i = 0; i < WIDTH * HEIGHT; i++)
    {
        uint32_t value = lift_host_read(host, base + 4 * i, 4);
        pixels[4 * i + 0] = (uint8_t)value;
        pixels[4 * i + 1] = (uint8_t)(value >> 8);
        pixels[4 * i + 2] = (uint8_t)(value >> 16);
        pixels[4 * i + 3] = 0xff;
    }
}

int main(void)
{
    const uint32_t masks[3] = {0x00ff0000, 0x0000ff00, 0x000000ff};
    VertrixSurface frame = {pixels, sizeof pixels, WIDTH, HEIGHT, WIDTH * 4, 4};
    static LiftHost host;
    uint8_t *heap;
    uint32_t heap_size;
    int lifted;
    uint32_t form, display, base, width, height, pitch, bytes, start;
    unsigned shown = 0;
    if (!vertrix_wii_video_init(&video))
    {
        return 1;
    }
    WPAD_Init();
    WPAD_SetDataFormat(WPAD_CHAN_0, WPAD_FMT_BTNS_ACC_IR);
    WPAD_SetVRes(WPAD_CHAN_0, 640, 480);
    SYS_STDIO_Report(true);
    if (vertrix_wii_archive_open(&archive) != VERTRIX_WII_ARCHIVE_OK)
    {
        fail("Could not read sd:/apps/vertrix2/Vertrix2.vf.");
    }
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
    host.archive = archive.archive;
    host.decode_jpeg = jpeg_decode;
    vertrix_lifted_allow_unverified(1);
    form = lift_host_allocate(&host, 0x1000);
    display = lift_host_allocate(&host, 0x800);
    host_store(&host, 0x544070, display);
    lift_host_run(&host, 0x4df307, 0, 0, 0, 0, &lifted); /* RTL thread-variable block */
    lift_host_run(&host, 0x475660, 0, 0, 0, 0, &lifted); /* input unit initialization */
    lift_host_run(&host, 0x41a080, form, 0, 0, 0, &lifted); /* master startup */
    printf("done master startup at %u ms\n", (unsigned)ticks_to_millisecs(gettime()));
    lift_host_run(&host, 0x41a540, form, 0, 0, 0, &lifted); /* loader */
    printf("done loader at %u ms\n", (unsigned)ticks_to_millisecs(gettime()));
    lift_host_run(&host, 0x45dca0, 0, 0, 0, 0, &lifted); /* sprite banks */
    printf("done sprite banks at %u ms\n", (unsigned)ticks_to_millisecs(gettime()));
    lift_host_run(&host, 0x45dca0, 0, 0, 0, 0, &lifted);    /* sprite banks */
    printf("done sprite banks at %u ms\n", (unsigned)ticks_to_millisecs(gettime()));
    base = lift_host_surface(&host, host.primary_surface, &width, &height, &pitch, &bytes);
    gather(&host, base);
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
        WPAD_ScanPads();
        if (WPAD_ButtonsDown(0) & WPAD_BUTTON_HOME)
        {
            break;
        }
        {
            /* The remote becomes the original's DirectInput keyboard: held sideways, the D-pad is
             * the arrow keys, A Enter, B Space, 1 and 2 Z and X, minus Escape. */
            static const struct { uint32_t button; unsigned scan_code; } keys[] = {
                {WPAD_BUTTON_UP, 0xc8}, {WPAD_BUTTON_DOWN, 0xd0}, {WPAD_BUTTON_LEFT, 0xcb},
                {WPAD_BUTTON_RIGHT, 0xcd}, {WPAD_BUTTON_A, 0x1c}, {WPAD_BUTTON_B, 0x39},
                {WPAD_BUTTON_1, 0x2c}, {WPAD_BUTTON_2, 0x2d}, {WPAD_BUTTON_MINUS, 0x01}};
            uint32_t down = WPAD_ButtonsDown(0), up = WPAD_ButtonsUp(0);
            unsigned k;
            for (k = 0; k < sizeof keys / sizeof keys[0]; k++)
            {
                if (down & keys[k].button)
                {
                    lift_host_key(&host, keys[k].scan_code, 1);
                }
                if (up & keys[k].button)
                {
                    lift_host_key(&host, keys[k].scan_code, 0);
                }
            }
            {
                /* The pointer is the original's DirectInput mouse: its position goes straight into
                 * the mouse object (x, y words at +0x48) and A also presses mouse button 0. */
                ir_t ir;
                WPAD_IR(0, &ir);
                if (ir.valid)
                {
                    int px = (int)ir.x < 0 ? 0 : (int)ir.x > 639 ? 639 : (int)ir.x;
                    int py = (int)ir.y < 0 ? 0 : (int)ir.y > 479 ? 479 : (int)ir.y;
                    host_store(&host, 0x5588f8 + 0x48, (uint32_t)px | ((uint32_t)py << 16));
                    lift_host_mouse(&host, 0, 0); /* a motion event makes the poll publish the position */
                }
                if (down & WPAD_BUTTON_A)
                {
                    lift_host_mouse(&host, 12, 0x80);
                }
                if (up & WPAD_BUTTON_A)
                {
                    lift_host_mouse(&host, 12, 0);
                }
            }
#ifdef VERTRIX_AUTOPLAY
            {
                /* Scripted pointer for unattended runs: the same walk through the menus the host
                 * tool makes (main menu, players selection, ready to fight, yes). */
                static unsigned n;
                static int started;
                static unsigned last_n;
                static const struct { unsigned at; int x, y; } moves[] = {
                    {150, 320, 350}, {190, 320, 402}, {230, 320, 402}, {320, 330, 130},
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
                /* the host tool steps the clock 120 ms per tick and its menu first runs at tick 89 */
                n = started ? 89 + (tick - menu_ms) / 120 : 89;
                ph = n >= 150 ? (n - 150) % 40 : 0;
                if (handler == 0x41c7b0 || handler == 0x41d0e0)
                {
                    /* players selection: the GO preview; ready to fight: YES */
                    host_store(&host, 0x5588f8 + 0x48, handler == 0x41c7b0 ? (330u | (130u << 16)) : (415u | (445u << 16)));
                }
                for (m = 0; m < sizeof moves / sizeof moves[0] && handler == 0x41b820; m++)
                {
                    if (moves[m].at <= n && moves[m].at > last_n)
                    {
                        host_store(&host, 0x5588f8 + 0x48, (uint32_t)moves[m].x | ((uint32_t)moves[m].y << 16));
                        printf("autoplay move %d %d at n %u\n", moves[m].x, moves[m].y, n);
                    }
                }
                {
                    static int pressed;
                    if (n >= 150 && ph >= 2 && ph < 25 && !pressed)
                    {
                        lift_host_mouse(&host, 12, 0x80);
                        pressed = 1;
                        printf("autoplay press at n %u, screen %u\n", n, (unsigned)lift_host_read(&host, 0x532a4c, 4));
                        printf("  mouse pos %u,%u raw %x flag553648 %x\n", (unsigned)lift_host_read(&host, 0x5588f8 + 0x48, 2), (unsigned)lift_host_read(&host, 0x5588f8 + 0x4a, 2), (unsigned)lift_host_read(&host, 0x558944, 4), (unsigned)lift_host_read(&host, 0x553648, 4));
                    }
                    if (n >= 150 && (ph >= 25 || ph < 2) && pressed)
                    {
                        lift_host_mouse(&host, 12, 0);
                        pressed = 0;
                    }
                }
                if (n >= 150 && n <= 160 && n != last_n)
                {
                    printf("  slot state %x list %x,%x,%x pending %u/%u\n", (unsigned)lift_host_read(&host, 0x5501c4, 1), (unsigned)lift_host_read(&host, 0x5501e4, 4), (unsigned)lift_host_read(&host, 0x5501e8, 4), (unsigned)lift_host_read(&host, 0x5501ec, 4), host.mouse_head, host.mouse_tail);
                }
                if (started)
                {
                    lift_host_mouse(&host, 0, 0);
                }
                if (started && n != last_n && (n == 156 || n == 170 || n == 200))
                {
                    uint32_t cnt = lift_host_read(&host, 0x546724, 4), arr = lift_host_read(&host, 0x546720, 4), q;
                    printf("  actors %u mouse %u,%u hover %x:", (unsigned)cnt, (unsigned)lift_host_read(&host, 0x5588f8 + 0x48, 2), (unsigned)lift_host_read(&host, 0x5588f8 + 0x4a, 2), (unsigned)lift_host_read(&host, 0x558944, 4));
                    for (q = 0; q < cnt && q < 12; q++)
                    {
                        uint32_t a = lift_host_read(&host, arr + 4 * q, 4);
                        printf(" [t%x h%x]", (unsigned)lift_host_read(&host, a + 0x14c, 4), (unsigned)lift_host_read(&host, a + 0x154, 4));
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
            lift_host_run(&host, 0x4b7b80, 0, 0, 0, 0, &lifted); /* the 14 ms timer: polls the devices */
        }
        {
            static unsigned loops;
            if (++loops % 5000 == 0)
            {
                printf("loop %u at %u ms, handler %x\n", loops, (unsigned)(tick - start), (unsigned)handler);
            }
        }
        host.clock_ms = tick - start;
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
        if (host.frames_presented != before)
        {
            base = lift_host_surface(&host, host.primary_surface, &width, &height, &pitch, &bytes);
            gather(&host, base);
            if (shown < 5)
            {
                printf("frame %u: handler %x, %u ms\n", shown++, (unsigned)handler,
                       (unsigned)(ticks_to_millisecs(gettime()) - tick));
            }
#ifdef VERTRIX_AUTOPLAY
            if (handler == 0x424990)
            {
                static unsigned gameplay_frames;
                if (++gameplay_frames == 600)
                {
                    FILE *shot = fopen("sd:/apps/vertrix2/shot.ppm", "wb");
                    if (shot != NULL)
                    {
                        unsigned i;
                        fprintf(shot, "P6\n%d %d\n255\n", WIDTH, HEIGHT);
                        for (i = 0; i < WIDTH * HEIGHT; i++)
                        {
                            fputc(pixels[4 * i + 2], shot);
                            fputc(pixels[4 * i + 1], shot);
                            fputc(pixels[4 * i + 0], shot);
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
            if (!vertrix_wii_frame_texture_update(&frame, masks, &texture) ||
                !vertrix_wii_frame_present(&video.presenter, &texture))
            {
                break;
            }
        }
    }
    vertrix_wii_texture_free(&texture);
    vertrix_wii_archive_close(&archive);
    return 0;
}
