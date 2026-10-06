#include "wii_video.h"
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

int vertrix_wii_video_init(VertrixWiiVideo *output)
{
    if (!output || output->ready || output->fifo || output->framebuffer_allocations[0] ||
        output->framebuffer_allocations[1])
    {
        return 0;
    }
    VIDEO_Init();
    GXRModeObj *preferred = VIDEO_GetPreferredMode(NULL);
    if (!preferred || !preferred->fbWidth || preferred->fbWidth > 640 || !preferred->efbHeight ||
        preferred->efbHeight > 528 || !preferred->xfbHeight || preferred->xfbHeight > 576)
    {
        return 0;
    }
    GXRModeObj mode = *preferred;
    /* Reserve the maximum copy height, independently of Y-scale rounding. */
    GXRModeObj allocation_mode = mode;
    allocation_mode.xfbHeight = 1024;
    void *first = SYS_AllocateFramebuffer(&allocation_mode);
    void *second = SYS_AllocateFramebuffer(&allocation_mode);
    void *fifo = memalign(32, 256 * 1024);
    if (!first || !second || !fifo)
    {
        free(first);
        free(second);
        free(fifo);
        return 0;
    }
    memset(fifo, 0, 256 * 1024);
    output->mode = mode;
    output->framebuffer_allocations[0] = first;
    output->framebuffer_allocations[1] = second;
    output->fifo = fifo;
    void *xfb_first = MEM_K0_TO_K1(first);
    void *xfb_second = MEM_K0_TO_K1(second);
    vertrix_wii_frame_presenter_init(&output->mode, xfb_first, xfb_second, &output->presenter);
    /* Keep the initially displayed buffer separate from the first draw target. */
    VIDEO_SetBlack(true);
    VIDEO_Configure(&output->mode);
    VIDEO_ClearFrameBuffer(&output->mode, xfb_first, COLOR_BLACK);
    VIDEO_ClearFrameBuffer(&output->mode, xfb_second, COLOR_BLACK);
    VIDEO_SetNextFramebuffer(xfb_second);
    VIDEO_Flush();
    VIDEO_WaitVSync();
    if (mode.viTVMode & VI_NON_INTERLACE)
    {
        VIDEO_WaitVSync();
    }
    GX_Init(fifo, 256 * 1024);
    GXColor black = {0, 0, 0, 255};
    GX_SetCopyClear(black, 0x00ffffff);
    GX_SetDispCopySrc(0, 0, mode.fbWidth, mode.efbHeight);
    unsigned copy_height = GX_SetDispCopyYScale(GX_GetYScaleFactor(mode.efbHeight, mode.xfbHeight));
    GX_SetDispCopyDst(mode.fbWidth, copy_height);
    GX_SetCopyFilter(mode.aa, output->mode.sample_pattern, GX_TRUE, output->mode.vfilter);
    GX_SetFieldMode(mode.field_rendering, mode.viHeight == 2 * mode.xfbHeight);
    GX_SetPixelFmt(mode.aa ? GX_PF_RGB565_Z16 : GX_PF_RGB8_Z24, GX_ZC_LINEAR);
    GX_SetDispCopyGamma(GX_GM_1_0);
    VIDEO_SetBlack(false);
    VIDEO_Flush();
    VIDEO_WaitVSync();
    output->ready = 1;
    return 1;
}
