/* The shell on the 3DS (shell/shell.h): the picture, scaled down to 240 lines at the game's
 * shape, on both screens (the bottom one is the touch screen, so touching the picture there is
 * pointing at it); the sound stream on the DSP at 32 kHz. libctru's frame buffers, no GPU. */
#include <3ds.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

#include "console.h"
#include "gfx.h"
#include "shell_common.h"

enum
{
    AUDIO_RATE = 32000,
    AUDIO_FRAMES = 1024,
    AUDIO_BUFFERS = 4,
    SCREEN_HEIGHT = 240,
    TOP_WIDTH = 400,
    BOTTOM_WIDTH = 320
};

/* The picture as the screens show it: up to 400x240, 0xRRGGBB. */
static uint32_t scaled[TOP_WIDTH * SCREEN_HEIGHT];
static unsigned scaled_width, frame_width, frame_height;
static int audio_ready;
static ndspWaveBuf wave[AUDIO_BUFFERS];
static int16_t *wave_data;
static volatile int audio_stop;
static pthread_t audio_thread;

/* --- sound --------------------------------------------------------------------------------- */

static void *audio_loop(void *unused)
{
    (void)unused;
    while (!audio_stop)
    {
        for (int i = 0; i < AUDIO_BUFFERS; ++i)
        {
            if (wave[i].status == NDSP_WBUF_FREE || wave[i].status == NDSP_WBUF_DONE)
            {
                common_audio_mix(wave[i].data_pcm16, AUDIO_FRAMES, AUDIO_RATE);
                DSP_FlushDataCache(wave[i].data_pcm16, AUDIO_FRAMES * 4);
                ndspChnWaveBufAdd(0, &wave[i]);
            }
        }
        svcSleepThread(4000000);
    }
    return NULL;
}

static void audio_start(void)
{
    /* The DSP needs its firmware (sdmc:/3ds/dspfirm.cdc); without it the games are silent. */
    if (R_FAILED(ndspInit()))
    {
        shell_log("sound: the DSP did not start (is sdmc:/3ds/dspfirm.cdc there?)");
        return;
    }
    wave_data = linearAlloc(AUDIO_BUFFERS * AUDIO_FRAMES * 4);
    if (!wave_data)
    {
        ndspExit();
        return;
    }
    memset(wave_data, 0, AUDIO_BUFFERS * AUDIO_FRAMES * 4);
    ndspSetOutputMode(NDSP_OUTPUT_STEREO);
    ndspChnSetInterp(0, NDSP_INTERP_LINEAR);
    ndspChnSetRate(0, AUDIO_RATE);
    ndspChnSetFormat(0, NDSP_FORMAT_STEREO_PCM16);
    memset(wave, 0, sizeof wave);
    for (int i = 0; i < AUDIO_BUFFERS; ++i)
    {
        wave[i].data_pcm16 = wave_data + i * AUDIO_FRAMES * 2;
        wave[i].nsamples = AUDIO_FRAMES;
    }
    audio_ready = 1;
    pthread_create(&audio_thread, NULL, audio_loop, NULL);
}

static void audio_end(void)
{
    if (!audio_ready)
    {
        return;
    }
    audio_stop = 1;
    pthread_join(audio_thread, NULL);
    ndspChnReset(0);
    ndspExit();
    linearFree(wave_data);
}

/* --- the screens --------------------------------------------------------------------------- */

const char *shell_start(int argc, char **argv, const ShellOptions *options)
{
    gfxInitDefault();
    console_init();
    const char *folder = common_start(argc, argv, options);
    audio_start();
    return folder;
}

/* Under the frame's lock: the picture scaled to 240 lines, each pixel the average of the ones
 * it covers. */
static void scale(const uint32_t *pixels, unsigned width, unsigned height, int fresh)
{
    if (!fresh && width == frame_width && height == frame_height)
    {
        return;
    }
    frame_width = width;
    frame_height = height;
    const double aspect =
        common_options.aspect > 0 ? common_options.aspect : (double)width / (double)height;
    unsigned w = (unsigned)(SCREEN_HEIGHT * aspect + 0.5);
    w = w > TOP_WIDTH ? TOP_WIDTH : w;
    scaled_width = w;
    for (unsigned y = 0; y < SCREEN_HEIGHT; ++y)
    {
        const unsigned y0 = y * height / SCREEN_HEIGHT;
        unsigned y1 = (y + 1) * height / SCREEN_HEIGHT;
        y1 = y1 > y0 ? y1 : y0 + 1;
        for (unsigned x = 0; x < w; ++x)
        {
            const unsigned x0 = x * width / w;
            unsigned x1 = (x + 1) * width / w;
            x1 = x1 > x0 ? x1 : x0 + 1;
            unsigned r = 0, g = 0, b = 0, n = 0;
            for (unsigned sy = y0; sy < y1; ++sy)
            {
                const uint32_t *row = pixels + sy * width;
                for (unsigned sx = x0; sx < x1; ++sx)
                {
                    r += row[sx] >> 16 & 255;
                    g += row[sx] >> 8 & 255;
                    b += row[sx] & 255;
                    ++n;
                }
            }
            scaled[y * TOP_WIDTH + x] = (r / n) << 16 | (g / n) << 8 | (b / n);
        }
    }
}

/* The scaled picture, centred, into a screen's frame buffer (BGR, columns bottom to top). */
static void blit(gfxScreen_t screen, unsigned screen_width)
{
    u16 fb_height, fb_width;
    uint8_t *fb = gfxGetFramebuffer(screen, GFX_LEFT, &fb_height, &fb_width);
    memset(fb, 0, (size_t)screen_width * SCREEN_HEIGHT * 3);
    const unsigned w = scaled_width < screen_width ? scaled_width : screen_width;
    const unsigned left = (screen_width - w) / 2, skip = (scaled_width - w) / 2;
    for (unsigned x = 0; x < w; ++x)
    {
        uint8_t *column = fb + (left + x) * SCREEN_HEIGHT * 3;
        for (unsigned y = 0; y < SCREEN_HEIGHT; ++y)
        {
            const uint32_t p = scaled[y * TOP_WIDTH + skip + x];
            uint8_t *out = column + (SCREEN_HEIGHT - 1 - y) * 3;
            out[0] = (uint8_t)p;
            out[1] = (uint8_t)(p >> 8);
            out[2] = (uint8_t)(p >> 16);
        }
    }
}

static void draw(void)
{
    if (common_error())
    {
        scale(common_error_canvas(), GFX_WIDTH, GFX_HEIGHT, 1);
    }
    else
    {
        common_show(scale);
    }
    if (scaled_width)
    {
        blit(GFX_TOP, TOP_WIDTH);
        blit(GFX_BOTTOM, BOTTOM_WIDTH);
    }
    gfxFlushBuffers();
    gfxSwapBuffers();
    gspWaitForVBlank();
}

/* The touch screen shows the picture too: a touch is a point on it. */
static uint32_t input(void)
{
    uint32_t pads[2];
    int touched, tx, ty;
    console_read_input(pads, &touched, &tx, &ty);
    const unsigned w = scaled_width < BOTTOM_WIDTH ? scaled_width : BOTTOM_WIDTH;
    const int left = (BOTTOM_WIDTH - (int)w) / 2;
    const int skip = ((int)scaled_width - (int)w) / 2;
    const int inside = touched && w && tx >= left && tx < left + (int)w;
    const int x = scaled_width ? (tx - left + skip) * (int)frame_width / (int)scaled_width : 0;
    const int y = ty * (int)frame_height / SCREEN_HEIGHT;
    common_input(pads, touched, inside, x, y);
    return pads[0];
}

_Noreturn void shell_run(void (*game)(void))
{
    if (game)
    {
        common_start_game(game);
    }
    uint32_t before = ~0u;
    uint64_t closing_since = 0;
    for (;;)
    {
        if (!aptMainLoop() && !closing_since)
        {
            common_request_quit();
            closing_since = console_microseconds();
        }
        const uint32_t pads = input();
        if (common_finished())
        {
            /* An error stays until a button is pressed (or the system closes the app). */
            if (!common_error() || closing_since || (pads & ~before))
            {
                break;
            }
        }
        /* The system waits for the app: give the game two seconds to close. */
        if (closing_since && console_microseconds() - closing_since > 2000000u)
        {
            break;
        }
        before = pads;
        draw();
    }
    audio_end();
    common_finish();
    gfxExit();
    exit(0);
}
