#ifndef VERTRIX_FRAME_COUNTER_H
#define VERTRIX_FRAME_COUNTER_H
#include <stdint.h>

typedef struct
{
    uint32_t frames;     /* 0x5329f8: frames drawn since the last report */
    uint32_t window;     /* 0x5329fc: clock sample at the last report */
    uint32_t sample;     /* 0x532a00: most recent clock sample */
    uint32_t per_second; /* 0x532a04: reported rate */
} VertrixFrameCounter;

enum
{
    VERTRIX_FRAME_WINDOW = 1000
};

/* Original0x41d670: take the millisecond clock sample (dword 0x5bd838). When fewer than 1000
 * ms (unsigned) passed since the window started, only the sample is stored. Otherwise the
 * rate becomes frames * 1000 / elapsed (32-bit unsigned arithmetic), the frame count is cleared
 * and the window restarts at the sample. */
void vertrix_frame_counter_update(VertrixFrameCounter *counter, uint32_t now);
#endif
