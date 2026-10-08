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
    HEAP_SIZE = 40 * 1024 * 1024,
    FRAME_MS = 33
};

static uint8_t image[LIFT_HOST_IMAGE_SIZE];
static VertrixWiiVideo video;
static VertrixWiiArchive archive;
static VertrixWiiTexture texture;
static uint8_t pixels[WIDTH * HEIGHT * 4];

static void host_store(LiftHost *host, uint32_t address, uint32_t value)
{
    unsigned i;
    for (i = 0; i < 4; i++)
    {
        uint8_t byte = (uint8_t)(value >> (8 * i));
        if (address >= LIFT_HOST_HEAP_BASE)
        {
            host->heap[address - LIFT_HOST_HEAP_BASE + i] = byte;
        }
        else
        {
            host->image[address - LIFT_HOST_IMAGE_BASE + i] = byte;
        }
    }
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
    int lifted;
    uint32_t form, display, base, width, height, pitch, bytes, start;
    unsigned shown = 0;
    if (!vertrix_wii_video_init(&video))
    {
        return 1;
    }
    WPAD_Init();
    SYS_STDIO_Report(true);
    if (vertrix_wii_archive_open(&archive) != VERTRIX_WII_ARCHIVE_OK)
    {
        fail("Could not read sd:/apps/vertrix2/Vertrix2.vf.");
    }
    heap = (uint8_t *)SYS_GetArena2Lo();
    if ((uint32_t)SYS_GetArena2Hi() - (uint32_t)heap < HEAP_SIZE)
    {
        fail("Not enough memory for the original's heap.");
    }
    SYS_SetArena2Lo(heap + HEAP_SIZE);
    printf("starting\n");
    lift_host_init(&host, image, image_bin, heap, HEAP_SIZE);
    host.archive = archive.archive;
    host.decode_jpeg = jpeg_decode;
    vertrix_lifted_allow_unverified(1);
    form = lift_host_allocate(&host, 0x1000);
    display = lift_host_allocate(&host, 0x800);
    host_store(&host, 0x544070, display);
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
        host.clock_ms = tick - start;
        lifted = 1;
        if (handler != 0)
        {
            lift_host_run(&host, handler, form, 0, 0, 0, &lifted);
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
