"""Record video initialization and allocation failures; no hardware execution."""
import argparse
import json
from pathlib import Path
import subprocess
from verify_wii_assets import HEADER
EXTRA = r'''
#include <stdbool.h>
    typedef struct
{
    unsigned viTVMode;
    unsigned short fbWidth, efbHeight, xfbHeight, viXOrigin, viYOrigin, viWidth, viHeight;
    unsigned xfbMode;
    unsigned char field_rendering, aa, sample_pattern[12][2], vfilter[7];
} GXRModeObj;
typedef struct
{
    unsigned char r, g, b, a;
} GXColor;
#define MEM_K0_TO_K1(x) (x)
#define COLOR_BLACK 0x10801080
#define VI_NON_INTERLACE 1
#define GX_TRUE 1
#define GX_PF_RGB565_Z16 1
#define GX_PF_RGB8_Z24 0
#define GX_ZC_LINEAR 0
#define GX_GM_1_0 0
void VIDEO_Init(void);
GXRModeObj *VIDEO_GetPreferredMode(GXRModeObj *);
void *SYS_AllocateFramebuffer(GXRModeObj *);
void VIDEO_SetBlack(bool);
void VIDEO_Configure(GXRModeObj *);
void VIDEO_ClearFrameBuffer(GXRModeObj *, void *, unsigned);
void VIDEO_SetNextFramebuffer(void *);
void VIDEO_Flush(void);
void VIDEO_WaitVSync(void);
void *GX_Init(void *, unsigned);
void GX_SetCopyClear(GXColor, unsigned);
void GX_SetDispCopySrc(unsigned short, unsigned short, unsigned short, unsigned short);
float GX_GetYScaleFactor(unsigned short, unsigned short);
unsigned GX_SetDispCopyYScale(float);
void GX_SetDispCopyDst(unsigned short, unsigned short);
void GX_SetCopyFilter(unsigned char, unsigned char[12][2], unsigned char, unsigned char[7]);
void GX_SetFieldMode(unsigned char, unsigned char);
void GX_SetPixelFmt(unsigned char, unsigned char);
void GX_SetDispCopyGamma(unsigned char);
'''
HARNESS = r'''
#include "wii_video.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
    static GXRModeObj mode;
static unsigned allocations, fail, releases, calls, waits, copies, configs, blacks;
static void *backing[3], *displayed;
static VertrixWiiVideo *active;
void *recorded_memalign(size_t align, size_t size)
{
    assert(align == 32 && size == 256 * 1024);
    unsigned n = ++allocations;
    if (n == fail)
        return NULL;
    backing[n - 1] = malloc(size);
    return backing[n - 1];
}
void recorded_free(void *p)
{
    if (p)
    {
        releases++;
        free(p);
    }
}
void VIDEO_Init(void)
{
    calls++;
}
GXRModeObj *VIDEO_GetPreferredMode(GXRModeObj *m)
{
    assert(!m);
    calls++;
    return &mode;
}
void *SYS_AllocateFramebuffer(GXRModeObj *m)
{
    assert(m->xfbHeight == 1024 && m->fbWidth == mode.fbWidth);
    unsigned n = ++allocations;
    if (n == fail)
        return NULL;
    backing[n - 1] = malloc(32);
    return backing[n - 1];
}
int vertrix_wii_frame_presenter_init(const GXRModeObj *m, void *a, void *b,
                                     VertrixWiiFramePresenter *p)
{
    assert(m == &active->mode && a == backing[0] && b == backing[1]);
    p->mode = m;
    p->buffers[0] = a;
    p->buffers[1] = b;
    p->next = 0;
    return 1;
}
void VIDEO_SetBlack(bool b)
{
    assert(b == (blacks == 0));
    blacks++;
    calls++;
}
void VIDEO_Configure(GXRModeObj *m)
{
    assert(m == &active->mode);
    configs++;
    calls++;
}
void VIDEO_ClearFrameBuffer(GXRModeObj *m, void *p, unsigned color)
{
    assert(m == &active->mode && p == backing[copies] && color == COLOR_BLACK);
    copies++;
    calls++;
}
void VIDEO_SetNextFramebuffer(void *p)
{
    assert(p == backing[1] && copies == 2);
    displayed = p;
    calls++;
}
void VIDEO_Flush(void)
{
    calls++;
}
void VIDEO_WaitVSync(void)
{
    waits++;
    calls++;
}
void *GX_Init(void *p, unsigned size)
{
    assert(p == backing[2] && size == 256 * 1024 && displayed == backing[1]);
    for (unsigned i = 0; i < size; i++)
        assert(((unsigned char *)p)[i] == 0);
    calls++;
    return p;
}
void GX_SetCopyClear(GXColor c, unsigned z)
{
    assert(!c.r && !c.g && !c.b && c.a == 255 && z == 0xffffff);
    calls++;
}
void GX_SetDispCopySrc(unsigned short x, unsigned short y, unsigned short w, unsigned short h)
{
    assert(!x && !y && w == mode.fbWidth && h == mode.efbHeight);
    calls++;
}
float GX_GetYScaleFactor(unsigned short e, unsigned short x)
{
    assert(e == mode.efbHeight && x == mode.xfbHeight);
    calls++;
    return 1.25f;
}
unsigned GX_SetDispCopyYScale(float s)
{
    assert(s == 1.25f);
    calls++;
    return mode.xfbHeight + 1;
}
void GX_SetDispCopyDst(unsigned short w, unsigned short h)
{
    assert(w == mode.fbWidth && h == mode.xfbHeight + 1);
    calls++;
}
void GX_SetCopyFilter(unsigned char a, unsigned char p[12][2], unsigned char v, unsigned char f[7])
{
    assert(a == mode.aa && v == 1 && !memcmp(p, mode.sample_pattern, 24) &&
           !memcmp(f, mode.vfilter, 7));
    calls++;
}
void GX_SetFieldMode(unsigned char f, unsigned char h)
{
    assert(f == mode.field_rendering && h == (mode.viHeight == 2 * mode.xfbHeight));
    calls++;
}
void GX_SetPixelFmt(unsigned char p, unsigned char z)
{
    assert(p == (mode.aa ? 1 : 0) && !z);
    calls++;
}
void GX_SetDispCopyGamma(unsigned char g)
{
    assert(!g);
    calls++;
}
int main(void)
{
    for (unsigned i = 0; i < 64; i++)
    {
        mode = (GXRModeObj){0};
        mode.viTVMode = i & 1;
        mode.fbWidth = (i & 2) ? 640 : 608;
        mode.efbHeight = (i & 4) ? 528 : 480;
        mode.xfbHeight = (i & 8) ? 576 : 480;
        mode.viHeight = mode.xfbHeight * ((i & 16) ? 2 : 1);
        mode.aa = (i & 32) != 0;
        mode.field_rendering = (i & 4) != 0;
        memset(mode.sample_pattern, 3, 24);
        memset(mode.vfilter, 4, 7);
        for (fail = 0; fail <= 3; fail++)
        {
            VertrixWiiVideo video = {0};
            active = &video;
            allocations = releases = calls = waits = copies = configs = blacks = 0;
            memset(backing, 0, sizeof(backing));
            int success = vertrix_wii_video_init(&video);
            if (fail)
            {
                VertrixWiiVideo zero = {0};
                assert(!success && !memcmp(&video, &zero, sizeof(video)));
                assert(allocations == 3 && releases == 2 && calls == 2 && !configs);
            }
            else
            {
                assert(success && video.ready && video.presenter.mode == &video.mode &&
                       video.presenter.next == 0);
                assert(video.fifo == backing[2] && video.framebuffer_allocations[0] == backing[0] &&
                       video.framebuffer_allocations[1] == backing[1]);
                assert(waits == 2 + (i & 1) && copies == 2 && configs == 1 && blacks == 2);
                unsigned previous = calls;
                assert(!vertrix_wii_video_init(&video) && calls == previous);
                for (unsigned j = 0; j < 3; j++)
                    free(backing[j]);
            }
        }
    }
    calls = allocations = 0;
    VertrixWiiVideo zero = {0};
    mode.fbWidth = 641;
    assert(!vertrix_wii_video_init(&zero) && calls == 2 && !allocations);
    calls = 0;
    assert(!vertrix_wii_video_init(NULL) && !calls);
    return 0;
}
'''


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--build-dir', type=Path, required=True)
    build = parser.parse_args().build_dir.resolve()
    build.mkdir(parents=True, exist_ok=True)
    root = Path(__file__).resolve().parents[1]
    (build / 'gccore.h').write_text(HEADER + EXTRA)
    (build / 'malloc.h').write_text('#include <stddef.h>\nvoid *recorded_memalign(size_t,size_t);\nvoid recorded_free(void*);\n#define memalign recorded_memalign\n#define free recorded_free\n')
    (build / 'harness.c').write_text(HARNESS)
    executable = build / 'verify-video'
    subprocess.run(['cc', '-std=c11', '-O2', '-Wall', '-Wextra', '-Werror', '-I', str(build), '-I', str(root / 'source'), str(build / 'harness.c'), str(root / 'source/wii_video.c'), '-o', str(executable)], check=True)
    subprocess.run([str(executable)], check=True)
    subprocess.run(['make', '-s', '-C', str(root), 'wii-video', f'BUILD={build / "powerpc"}'], check=True)
    report = {'status': 'passed', 'recorded_mode_configurations': 64, 'allocation_failure_cases': 192, 'scope': 'Host assertions check preferred-mode propagation, XFB reserve, allocation rollback, ' 'zeroed FIFO, initial buffer separation, copy-height rounding, filtering, field ' 'and pixel format selection. Actual PowerPC/libogc compilation passes. ' 'Hardware output and the complete application remain unverified.'}
    (build / 'wii-video-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))
if __name__ == '__main__':
    main()
