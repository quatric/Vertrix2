#include "wii_frame_present.h"

static volatile uint32_t retraces;

static void count_retrace(uint32_t count)
{
    (void)count;
    retraces++;
}

int vertrix_wii_frame_presenter_init(const GXRModeObj *mode, void *first, void *second,
                                     VertrixWiiFramePresenter *output)
{
    if (!output || !mode || !mode->fbWidth || !mode->efbHeight || !mode->xfbHeight || !first ||
        !second || first == second)
    {
        return 0;
    }
    VIDEO_SetPostRetraceCallback(count_retrace);
    VertrixWiiFramePresenter result = {mode, {first, second}, 0, retraces - 1};
    *output = result;
    return 1;
}

int vertrix_wii_frame_present(VertrixWiiFramePresenter *presenter, VertrixWiiTexture *texture)
{
    if (!presenter || !presenter->mode || !presenter->mode->fbWidth ||
        !presenter->mode->efbHeight || !presenter->mode->xfbHeight || presenter->next > 1 ||
        !presenter->buffers[0] || !presenter->buffers[1] ||
        presenter->buffers[0] == presenter->buffers[1] || !texture || !texture->ready ||
        !texture->pixels.data || texture->pixels.width != 640 || texture->pixels.height != 480 ||
        !(texture->u_limit > 0 && texture->u_limit <= 1) ||
        !(texture->v_limit > 0 && texture->v_limit <= 1))
    {
        return 0;
    }
    const GXRModeObj *mode = presenter->mode;
    if (mode->field_rendering)
    {
        GX_SetViewportJitter(0, 0, mode->fbWidth, mode->efbHeight, 0, 1, VIDEO_GetNextField());
    }
    else
    {
        GX_SetViewport(0, 0, mode->fbWidth, mode->efbHeight, 0, 1);
    }
    GX_SetScissor(0, 0, mode->fbWidth, mode->efbHeight);
    Mtx model;
    Mtx44 projection;
    guMtxIdentity(model);
    GX_LoadPosMtxImm(model, GX_PNMTX0);
    GX_SetCurrentMtx(GX_PNMTX0);
    guOrtho(projection, 0, 480, 0, 640, 0, 1);
    GX_LoadProjectionMtx(projection, GX_ORTHOGRAPHIC);
    vertrix_wii_frame_draw(texture, 0, 0, 640, 480);
    if (retraces == presenter->flipped)
    {
        VIDEO_WaitVSync();
    }
    GX_CopyDisp(presenter->buffers[presenter->next], GX_FALSE);
    GX_DrawDone();
    VIDEO_SetNextFramebuffer(presenter->buffers[presenter->next]);
    VIDEO_Flush();
    presenter->flipped = retraces;
    presenter->next ^= 1;
    return 1;
}
