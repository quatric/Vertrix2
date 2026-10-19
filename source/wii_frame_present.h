#ifndef VERTRIX_WII_FRAME_PRESENT_H
#define VERTRIX_WII_FRAME_PRESENT_H
#include "wii_frame_draw.h"

typedef struct
{
    const GXRModeObj *mode;
    void *buffers[2];
    unsigned next;
    uint32_t flipped; /* the retrace count when the last frame was scheduled */
} VertrixWiiFramePresenter;

/* Caller initializes GX and VIDEO, configures display copy/filter/scaling for
 * mode, and provides two independent XFBs of sufficient size. All are borrowed
 * and must remain live. The first presentation uses buffers[0]. */
int vertrix_wii_frame_presenter_init(const GXRModeObj *mode, void *first, void *second,
                                     VertrixWiiFramePresenter *output);
/* Present the completed original 640x480 frame, filling the configured viewport.
 * Waits for the copy before scheduling the XFB. The buffer it copies into was shown
 * two frames ago; it waits for vertical sync first only when no retrace has passed
 * since the last frame was scheduled, so that buffer may still be on screen. A slow
 * game is not held back to the next retrace. No gameplay clock advancement here. */
int vertrix_wii_frame_present(VertrixWiiFramePresenter *presenter, VertrixWiiTexture *texture);
#endif
