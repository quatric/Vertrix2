""
    "Verify presentation sequencing with recorded calls, without executing a GPU."
    "" import argparse import json from pathlib import Path import subprocess from verify_wii_assets
        import HEADER

            EXTRA = r''' typedef float Mtx[3][4];
typedef float Mtx44[4][4];
typedef struct
{
    unsigned short fbWidth, efbHeight, xfbHeight;
    unsigned char field_rendering;
} GXRModeObj;
#define GX_PNMTX0 0
#define GX_ORTHOGRAPHIC 1
void GX_SetViewport(float, float, float, float, float, float);
void GX_SetViewportJitter(float, float, float, float, float, float, unsigned);
unsigned VIDEO_GetNextField(void);
void GX_SetScissor(unsigned, unsigned, unsigned, unsigned);
void guMtxIdentity(Mtx);
void GX_LoadPosMtxImm(Mtx, unsigned);
void GX_SetCurrentMtx(unsigned);
void guOrtho(Mtx44, float, float, float, float, float, float);
void GX_LoadProjectionMtx(Mtx44, unsigned char);
void GX_CopyDisp(void *, unsigned char);
void GX_DrawDone(void);
void VIDEO_SetNextFramebuffer(void *);
void VIDEO_Flush(void);
void VIDEO_WaitVSync(void);
'''

    HARNESS = r'''
#include "wii_frame_present.h"
#include <assert.h>
#include <math.h>
#include <string.h>
    static unsigned events[32],
    count, field, waits;
static void *copied, *scheduled;
static GXRModeObj mode;
static void event(unsigned n)
{
    assert(count < 32);
    events[count++] = n;
}
void GX_SetViewport(float x, float y, float w, float h, float n, float f)
{
    assert(x == 0 && y == 0 && w == mode.fbWidth && h == mode.efbHeight && n == 0 && f == 1);
    event(1);
}
unsigned VIDEO_GetNextField(void)
{
    event(15);
    return field;
}
void GX_SetViewportJitter(float x, float y, float w, float h, float n, float f, unsigned v)
{
    assert(v == field);
    GX_SetViewport(x, y, w, h, n, f);
    events[count - 1] = 2;
}
void GX_SetScissor(unsigned x, unsigned y, unsigned w, unsigned h)
{
    assert(!x && !y && w == mode.fbWidth && h == mode.efbHeight);
    event(3);
}
void guMtxIdentity(Mtx m)
{
    memset(m, 0, sizeof(Mtx));
    m[0][0] = m[1][1] = m[2][2] = 1;
    event(4);
}
void GX_LoadPosMtxImm(Mtx m, unsigned n)
{
    assert(!n);
    for (unsigned y = 0; y < 3; y++)
        for (unsigned x = 0; x < 4; x++)
            assert(m[y][x] == (float)(x == y));
    event(5);
}
void GX_SetCurrentMtx(unsigned n)
{
    assert(!n);
    event(6);
}
void guOrtho(Mtx44 m, float t, float b, float l, float r, float n, float f)
{
    assert(t == 0 && b == 480 && l == 0 && r == 640 && n == 0 && f == 1);
    memset(m, 0, sizeof(Mtx44));
    m[0][0] = 42;
    event(7);
}
void GX_LoadProjectionMtx(Mtx44 m, unsigned char type)
{
    assert(m[0][0] == 42 && type == 1);
    event(8);
}
int vertrix_wii_frame_draw(VertrixWiiTexture *t, int16_t x, int16_t y, uint16_t w, uint16_t h)
{
    assert(t->ready && !x && !y && w == 640 && h == 480);
    event(9);
    return 1;
}
void GX_CopyDisp(void *p, unsigned char clear)
{
    assert(p && !clear);
    copied = p;
    event(10);
}
void GX_DrawDone(void)
{
    event(11);
}
void VIDEO_SetNextFramebuffer(void *p)
{
    assert(p == copied && events[count - 1] == 11);
    scheduled = p;
    event(12);
}
void VIDEO_Flush(void)
{
    event(13);
}
void VIDEO_WaitVSync(void)
{
    assert(events[count - 1] == 13);
    waits++;
    event(14);
}
int main(void)
{
    unsigned char buffers[2][32];
    VertrixWiiFramePresenter presenter;
    VertrixWiiTexture texture = {0};
    texture.ready = 1;
    texture.pixels.data = buffers[0];
    texture.pixels.width = 640;
    texture.pixels.height = 480;
    texture.u_limit = 1;
    texture.v_limit = 1;
    mode.fbWidth = 640;
    mode.efbHeight = 480;
    mode.xfbHeight = 480;
    assert(vertrix_wii_frame_presenter_init(&mode, buffers[0], buffers[1], &presenter));
    for (unsigned i = 0; i < 2048; i++)
    {
        count = 0;
        field = i & 1;
        mode.field_rendering = (i / 2) & 1;
        mode.fbWidth = (i & 4) ? 640 : 608;
        mode.efbHeight = (i & 8) ? 480 : 240;
        assert(vertrix_wii_frame_present(&presenter, &texture));
        assert(presenter.next == ((i + 1) & 1) && copied == buffers[i & 1] && scheduled == copied);
        unsigned offset = mode.field_rendering ? 1 : 0;
        assert(count == 13 + offset);
        if (offset)
            assert(events[0] == 15);
        assert(events[offset] == (offset ? 2 : 1));
        for (unsigned j = 1; j < 13; j++)
            assert(events[offset + j] == j + 2);
        count = 0;
        VertrixWiiFramePresenter before = presenter;
        texture.u_limit = NAN;
        assert(!vertrix_wii_frame_present(&presenter, &texture));
        assert(!count && !memcmp(&before, &presenter, sizeof(before)));
        texture.u_limit = 1;
        texture.pixels.width = 639;
        assert(!vertrix_wii_frame_present(&presenter, &texture));
        assert(!count && !memcmp(&before, &presenter, sizeof(before)));
        texture.pixels.width = 640;
        presenter.next = 2;
        assert(!vertrix_wii_frame_present(&presenter, &texture));
        assert(!count);
        presenter = before;
        assert(!vertrix_wii_frame_presenter_init(&mode, buffers[0], buffers[0], &presenter));
        assert(!memcmp(&before, &presenter, sizeof(before)));
    }
    assert(waits == 2048);
    assert(!vertrix_wii_frame_present(NULL, &texture));
    assert(!vertrix_wii_frame_present(&presenter, NULL));
    return 0;
}
'''

    def
    main()
    : parser = argparse.ArgumentParser(description = __doc__) parser.add_argument(
          '--build-dir', type = Path, required = True) args = parser.parse_args() build =
          args.build_dir.resolve() build.mkdir(parents = True, exist_ok = True) root =
              Path(__file__)
                  .resolve()
                  .parents[1](build / 'gccore.h')
                  .write_text(HEADER + EXTRA)(build / 'harness.c')
                  .write_text(HARNESS) executable =
                  build /
                  'verify-present' subprocess
                      .run(
                          [
                              'cc', '-std=c11', '-O2', '-Wall', '-Wextra', '-Werror', '-I',
                              str(build), '-I', str(root / 'source'), str(build / 'harness.c'),
                              str(root / 'source/wii_frame_present.c'), '-o', str(executable)
                          ],
                          check = True) subprocess.run([str(executable)], check = True)
                          subprocess.run(
                              [
                                  'make', '-s', '-C', str(root), 'wii-frame-present',
                                  f 'BUILD={build / "powerpc"}'
                              ],
                              check = True) report = {
                      'status' : 'passed',
                      'recorded_presentations' : 2048,
                      'invalid_preservation_cases' : 8192,
                      'scope' :
                          'Host records projection setup, progressive/field viewport selection, ' 'draw/copy/completion/display/flush/vsync ordering and alternating XFBs. ' 'Actual PowerPC/libogc compilation passes. GPU execution, allocated XFB ' 'sizes, video/copy initialization, timing and complete game remain unverified.'
                  }(build / 'wii-frame-present-verification.json')
                                                         .write_text(
                                                             json.dumps(report, indent = 2) + '\n')
                                                             print(json.dumps(report, indent = 2))

                                                                 if __name__
                                                     == '__main__' : main()
