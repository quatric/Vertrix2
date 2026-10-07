/* Runs the lifted screen builders on the Wii through the dispatcher and lists the calls that
 * reach the platform boundary. Not the game loop. The original's mapped image is linked in
 * (build/image.bin, from tools/dump_image.py). */
#include <gccore.h>
#include <stdio.h>
#include <stdlib.h>
#include <wiiuse/wpad.h>

#include "lift_host.h"

extern const uint8_t image_bin[];

static uint8_t image[LIFT_HOST_IMAGE_SIZE];
static uint8_t heap[0x400000];

static void run(const char *name, uint32_t target)
{
    LiftHost host;
    int lifted;
    unsigned i;
    uint32_t result;
    lift_host_init(&host, image, image_bin, heap, sizeof heap);
    result = lift_host_run(&host, target, 0, 0xffffffffu, 0, 0, &lifted);
    printf("%s %06x: %s result %x, %u boundary calls, heap %x\n", name, (unsigned)target,
           lifted ? "lifted" : "missing", (unsigned)result, host.boundary_calls,
           (unsigned)host.heap_top);
    for (i = 0; i < host.boundary_distinct; i++)
    {
        printf("  boundary %06x x%u\n", (unsigned)host.boundary_targets[i],
               host.boundary_counts[i]);
    }
}

int main(void)
{
    GXRModeObj *mode;
    void *framebuffer;
    VIDEO_Init();
    WPAD_Init();
    mode = VIDEO_GetPreferredMode(NULL);
    framebuffer = MEM_K0_TO_K1(SYS_AllocateFramebuffer(mode));
    console_init(framebuffer, 20, 20, mode->fbWidth, mode->xfbHeight, mode->fbWidth * 2);
    VIDEO_Configure(mode);
    VIDEO_SetNextFramebuffer(framebuffer);
    VIDEO_SetBlack(FALSE);
    VIDEO_Flush();
    VIDEO_WaitVSync();
    SYS_STDIO_Report(true);
    printf("\nVertrix 2 lifted routines on the Wii: %u in the dispatcher\n\n",
           vertrix_lifted_count());
    run("hud_decor", 0x46b810);
    run("title_screen", 0x465af0);
    run("select_screen", 0x466d60);
    run("game_screen", 0x46c9d0);
    printf("\ndone (HOME exits)\n");
    for (;;)
    {
        WPAD_ScanPads();
        if (WPAD_ButtonsDown(0) & WPAD_BUTTON_HOME)
        {
            exit(0);
        }
        VIDEO_WaitVSync();
    }
}
