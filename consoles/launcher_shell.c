/* The Wii launcher (launcher/main.c) on a console: its canvas, controllers, music and starting of
 * games through the console shell (shell/shell.h, console.h), behind the libogc, libwiiinput and
 * libwiiupdate calls it makes (compat/launcher_compat.h). launcher/main.c is compiled with its
 * main renamed launcher_main; it runs on the shell's game thread. */
#define VERTRIX_LAUNCHER_SHELL /* this file's main is the program's */

#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

#include "app.h"
#include "compat/launcher_compat.h"
#include "gfx.h"
#include "shell.h"
#include "shell_common.h"

int launcher_main(int argc, char **argv);

u64 gettime(void)
{
    return shell_microseconds();
}

/* --- the canvas ---------------------------------------------------------------------------- */

void gfx_init(void)
{
}

void gfx_present(void)
{
    shell_present(gfx_canvas(), GFX_WIDTH, GFX_HEIGHT);
    shell_wait_frame();
}

void gfx_black(void)
{
}

int gfx_widescreen(void)
{
    return 0;
}

/* --- the controllers ----------------------------------------------------------------------- */

static u32 held, held_before, tapped;
static int cursor_x, cursor_y, cursor_active, cursor_moved, touching;

s32 INPUT_Init(void)
{
    return 0;
}

void INPUT_Shutdown(void)
{
}

void INPUT_SetScreenSize(int width, int height)
{
    (void)width;
    (void)height;
}

void INPUT_Update(void)
{
    static const struct
    {
        uint32_t shell;
        u32 wpad;
    } map[] = {{SHELL_PAD_UP, WPAD_BUTTON_UP},
               {SHELL_PAD_DOWN, WPAD_BUTTON_DOWN},
               {SHELL_PAD_LEFT, WPAD_BUTTON_LEFT},
               {SHELL_PAD_RIGHT, WPAD_BUTTON_RIGHT},
               {SHELL_PAD_B, WPAD_BUTTON_A},
               {SHELL_PAD_A, WPAD_BUTTON_B},
               {SHELL_PAD_Y, WPAD_BUTTON_1},
               {SHELL_PAD_X, WPAD_BUTTON_2},
               {SHELL_PAD_SHOULDER_L, WPAD_BUTTON_MINUS},
               {SHELL_PAD_SHOULDER_R, WPAD_BUTTON_PLUS},
               {SHELL_PAD_MENU, WPAD_BUTTON_HOME}};
    const uint32_t pads = shell_pad(0) | shell_pad(1);
    held_before = held;
    held = 0;
    for (unsigned i = 0; i < sizeof map / sizeof map[0]; ++i)
    {
        held |= pads & map[i].shell ? map[i].wpad : 0;
    }
    /* The touch screen: the pointer while touched, and A where it was let go. */
    int x, y;
    tapped = 0;
    if (shell_pointer(&x, &y))
    {
        cursor_moved = !cursor_active || x != cursor_x || y != cursor_y;
        cursor_x = x;
        cursor_y = y;
        cursor_active = touching = 1;
    }
    else if (touching)
    {
        touching = 0;
        cursor_moved = 0;
        tapped = WPAD_BUTTON_A; /* the cursor stays for this frame, where the tap was */
    }
    else
    {
        cursor_active = cursor_moved = 0;
    }
}

u32 INPUT_ButtonsHeld(void)
{
    return held;
}

u32 INPUT_ButtonsDown(void)
{
    return (held & ~held_before) | tapped;
}

float INPUT_Stick(int which, float *x, float *y, const char **source)
{
    (void)which;
    (void)source;
    *x = *y = 0.0f;
    return 0.0f;
}

bool INPUT_CursorActive(void)
{
    return cursor_active;
}

void INPUT_CursorPosition(int *x, int *y)
{
    *x = cursor_x;
    *y = cursor_y;
}

bool INPUT_CursorMoved(void)
{
    return cursor_moved;
}

void INPUT_MouseDelta(int *dx, int *dy, int *wheel)
{
    *dx = *dy = *wheel = 0;
}

/* --- the music ----------------------------------------------------------------------------- */

void ASND_Init(void)
{
}

void ASND_End(void)
{
}

void ASND_Pause(s32 paused)
{
    common_audio_pause(paused);
}

enum
{
    INPUT_SIZE = 16384
};

static pthread_t decoder;
static volatile int decoding, stop_decoding;
static volatile u32 volume = 255;
static void *reader_data;
static s32 (*reader)(void *, void *, s32);
static void (*filter)(struct mad_stream *, struct mad_frame *);

static int16_t sample(mad_fixed_t value)
{
    value += 1L << (MAD_F_FRACBITS - 16); /* round */
    value = value >= MAD_F_ONE ? MAD_F_ONE - 1 : (value < -MAD_F_ONE ? -MAD_F_ONE : value);
    return (int16_t)((value >> (MAD_F_FRACBITS + 1 - 16)) * (int)volume / 255);
}

/* The file to the end: frames decoded, synthesised and queued on the shell's stream, which
 * paces the thread. The stream's samples are little-endian, as the games' are. */
static void *decode(void *unused)
{
    (void)unused;
    static unsigned char input[INPUT_SIZE + MAD_BUFFER_GUARD];
    static uint8_t out[1152 * 4];
    struct mad_stream stream;
    struct mad_frame frame;
    struct mad_synth synth;
    mad_stream_init(&stream);
    mad_frame_init(&frame);
    mad_synth_init(&synth);
    unsigned rate = 0;
    int end = 0;
    while (!stop_decoding)
    {
        if (stream.buffer == NULL || stream.error == MAD_ERROR_BUFLEN)
        {
            if (end)
            {
                break;
            }
            size_t kept = 0;
            if (stream.next_frame != NULL)
            {
                kept = (size_t)(stream.bufend - stream.next_frame);
                memmove(input, stream.next_frame, kept);
            }
            s32 got = reader(reader_data, input + kept, (s32)(INPUT_SIZE - kept));
            if (got <= 0)
            {
                /* The last frame needs MAD_BUFFER_GUARD zero bytes after it. */
                end = 1;
                memset(input + kept, 0, MAD_BUFFER_GUARD);
                got = MAD_BUFFER_GUARD;
            }
            mad_stream_buffer(&stream, input, kept + (size_t)got);
            stream.error = MAD_ERROR_NONE;
        }
        if (mad_frame_decode(&frame, &stream) != 0)
        {
            if (MAD_RECOVERABLE(stream.error) || stream.error == MAD_ERROR_BUFLEN)
            {
                continue;
            }
            break;
        }
        if (filter)
        {
            filter(&stream, &frame);
        }
        mad_synth_frame(&synth, &frame);
        if (synth.pcm.samplerate != rate)
        {
            rate = synth.pcm.samplerate;
            shell_audio_open(rate, 2, 16);
        }
        const unsigned stereo = synth.pcm.channels == 2;
        for (unsigned i = 0; i < synth.pcm.length; ++i)
        {
            const int16_t left = sample(synth.pcm.samples[0][i]);
            const int16_t right = stereo ? sample(synth.pcm.samples[1][i]) : left;
            out[4 * i] = (uint8_t)left;
            out[4 * i + 1] = (uint8_t)((uint16_t)left >> 8);
            out[4 * i + 2] = (uint8_t)right;
            out[4 * i + 3] = (uint8_t)((uint16_t)right >> 8);
        }
        shell_audio_write(out, synth.pcm.length * 4u);
    }
    mad_synth_finish(&synth);
    mad_frame_finish(&frame);
    mad_stream_finish(&stream);
    decoding = 0;
    return NULL;
}

void MP3Player_Init(void)
{
}

void MP3Player_Stop(void)
{
    if (!decoder)
    {
        return;
    }
    stop_decoding = 1;
    shell_audio_open(44100, 2, 16); /* empties the queue, so a waiting write returns */
    pthread_join(decoder, NULL);
    decoder = 0;
    shell_audio_open(44100, 2, 16);
}

s32 MP3Player_PlayFile(void *cb_data, s32 (*read)(void *, void *, s32),
                       void (*filterfunc)(struct mad_stream *, struct mad_frame *))
{
    MP3Player_Stop();
    reader_data = cb_data;
    reader = read;
    filter = filterfunc;
    stop_decoding = 0;
    decoding = 1;
    if (pthread_create(&decoder, NULL, decode, NULL) != 0)
    {
        decoding = 0;
        decoder = 0;
        return -1;
    }
    return 0;
}

/* Until the last frame has played, not only been decoded. */
bool MP3Player_IsPlaying(void)
{
    return decoding || shell_audio_queued() > 0;
}

void MP3Player_Volume(u32 value)
{
    volume = value > 255 ? 255 : value;
}

/* --- starting a game ----------------------------------------------------------------------- */

int vertrix_app_boot(const char *path, int argc, const char *const *args)
{
    struct stat info;
    if (stat(path, &info) != 0 || !common_chain(path, argc > 1 ? args[1] : NULL))
    {
        return -1;
    }
    MP3Player_Stop();
    shell_exit(0);
}

/* --- the program --------------------------------------------------------------------------- */

static int saved_argc;
static char **saved_argv;

static void launcher(void)
{
    launcher_main(saved_argc, saved_argv);
    MP3Player_Stop();
    shell_exit(0);
}

int main(int argc, char **argv)
{
    static const ShellOptions options = {NULL, GFX_WIDTH, GFX_HEIGHT, 4.0 / 3.0, 0};
    shell_start(argc, argv, &options);
    shell_log_open("launcher.log");
    saved_argc = argc;
    saved_argv = argv;
    shell_run(launcher);
}
