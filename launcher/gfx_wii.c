/* The launcher's canvas (gfx.c) on the Wii: converted to the TV's YUV frame buffer once a
 * field. */
#include "gfx.h"

#include <gccore.h>
#include <malloc.h>

static GXRModeObj *mode;
static uint32_t *xfb[2];
static int current;
static int wide;

void gfx_init(void)
{
    VIDEO_Init();
    mode = VIDEO_GetPreferredMode(NULL);
    wide = CONF_GetAspectRatio() == CONF_ASPECT_16_9;
    VIDEO_Configure(mode);
    for (int i = 0; i < 2; ++i)
    {
        xfb[i] = (uint32_t *)MEM_K0_TO_K1(SYS_AllocateFramebuffer(mode));
        VIDEO_ClearFrameBuffer(mode, xfb[i], COLOR_BLACK);
    }
    VIDEO_SetNextFramebuffer(xfb[0]);
    VIDEO_SetBlack(FALSE);
    VIDEO_Flush();
    VIDEO_WaitVSync();
    if (mode->viTVMode & VI_NON_INTERLACE)
    {
        VIDEO_WaitVSync();
    }
}

int gfx_widescreen(void)
{
    return wide;
}

/* Two pixels to one Y0 Cb Y1 Cr word (ITU-R BT.601, studio range). */
static uint32_t yuyv(uint32_t a, uint32_t b)
{
    const int r0 = (int)(a >> 16 & 255), g0 = (int)(a >> 8 & 255), b0 = (int)(a & 255);
    const int r1 = (int)(b >> 16 & 255), g1 = (int)(b >> 8 & 255), b1 = (int)(b & 255);
    const int y0 = (66 * r0 + 129 * g0 + 25 * b0 + 128 + 4096) >> 8;
    const int y1 = (66 * r1 + 129 * g1 + 25 * b1 + 128 + 4096) >> 8;
    const int r = r0 + r1, g = g0 + g1, bl = b0 + b1;
    const int cb = (-38 * r - 74 * g + 112 * bl + 256 + 65536) >> 9;
    const int cr = (112 * r - 94 * g - 18 * bl + 256 + 65536) >> 9;
    return (uint32_t)y0 << 24 | (uint32_t)cb << 16 | (uint32_t)y1 << 8 | (uint32_t)cr;
}

void gfx_present(void)
{
    current ^= 1;
    uint32_t *out = xfb[current];
    const int lines = mode->xfbHeight, words = mode->fbWidth / 2;
    const int top = lines > GFX_HEIGHT ? (lines - GFX_HEIGHT) / 2 : 0;
    const uint32_t black = 0x10801080u;
    for (int y = 0; y < lines; ++y)
    {
        uint32_t *row = out + y * words;
        /* A 480-line canvas on a 480-line TV mode; taller PAL modes get black bars. */
        const int source = lines < GFX_HEIGHT ? y * GFX_HEIGHT / lines : y - top;
        if (source < 0 || source >= GFX_HEIGHT)
        {
            for (int x = 0; x < words; ++x)
            {
                row[x] = black;
            }
            continue;
        }
        const uint32_t *in = gfx_canvas() + source * GFX_WIDTH;
        for (int x = 0; x < words && 2 * x + 1 < GFX_WIDTH; ++x)
        {
            row[x] = yuyv(in[2 * x], in[2 * x + 1]);
        }
    }
    VIDEO_SetNextFramebuffer(out);
    VIDEO_Flush();
    VIDEO_WaitVSync();
}

void gfx_black(void)
{
    VIDEO_SetBlack(TRUE);
    VIDEO_Flush();
    VIDEO_WaitVSync();
}
