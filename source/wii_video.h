#ifndef VERTRIX_WII_VIDEO_H
#define VERTRIX_WII_VIDEO_H
#include "wii_frame_present.h"

typedef struct
{
    GXRModeObj mode;
    void *framebuffer_allocations[2];
    void *fifo;
    VertrixWiiFramePresenter presenter;
    unsigned ready;
} VertrixWiiVideo;

/* Initialize once with zero output. Owns the GX FIFO and two XFB allocations
 * until application exit; do not move or release the initialized context while
 * VIDEO/GX reference it. Uses the console's preferred mode. Allocation failures
 * release temporary backing and preserve output before configuring GX/VIDEO. */
int vertrix_wii_video_init(VertrixWiiVideo *output);
#endif
