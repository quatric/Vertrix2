/* The shell (shell/shell.h) as every console has it: the game's folder, the log, the clock, the
 * picture handed from the game's thread to the main one, the input queue, the sound stream's
 * queue, and what happens when the game ends. */
#include "shell_common.h"

#include <ctype.h>
#include <dirent.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/stat.h>
#include <unistd.h>

#include "console.h"
#include "gfx.h"

ShellOptions common_options;
static char folder[256];

uint64_t shell_microseconds(void)
{
    return console_microseconds();
}

/* --- the game's folder --------------------------------------------------------------------- */

/* Whether `directory` holds `name`, in any case. */
static int has_file(const char *directory, const char *name)
{
    DIR *dir = opendir(directory);
    if (!dir)
    {
        return 0;
    }
    int found = 0;
    struct dirent *entry;
    while (!found && (entry = readdir(dir)) != NULL)
    {
        found = strcasecmp(entry->d_name, name) == 0;
    }
    closedir(dir);
    return found;
}

int __attribute__((weak)) console_import_bundled(const char *folder)
{
    (void)folder;
    return 0;
}

const char *common_start(int argc, char **argv, const ShellOptions *options)
{
    common_options = *options;
    const char *app = console_app_folder();
    mkdir(app, 0777);
    if (!options->game)
    {
        snprintf(folder, sizeof folder, "%s", app);
        char music[300];
        snprintf(music, sizeof music, "%s/music", app);
        struct stat info;
        if (stat(music, &info) != 0)
        {
            console_import_bundled(app);
        }
        return folder;
    }
    /* The launcher passes the folder; started alone, the game uses its own in the app's. */
    if (argc >= 2 && argv[1] && strchr(argv[1], '/'))
    {
        snprintf(folder, sizeof folder, "%s", argv[1]);
    }
    else
    {
        snprintf(folder, sizeof folder, "%s/%s", app, options->game->folder);
    }
    mkdir(folder, 0777);
    if (!has_file(folder, options->game->needs))
    {
        console_import_bundled(folder);
    }
    if (!has_file(folder, options->game->needs))
    {
        char text[512];
        snprintf(text, sizeof text,
                 "%s needs the original game's files. Copy %s into %s/ on the SD card.",
                 options->game->title, options->game->needs_text, folder);
        shell_fatal(text);
    }
    return folder;
}

/* --- resources ----------------------------------------------------------------------------- */

/* The image the recompiler wrote, built into the program by bin2s (the Makefiles); a game has
 * one of them. */
extern const uint8_t v3_image_bin[] __attribute__((weak));
extern const uint32_t v3_image_bin_size __attribute__((weak));
extern const uint8_t v1_image_bin[] __attribute__((weak));
extern const uint32_t v1_image_bin_size __attribute__((weak));

uint8_t *shell_resource(const char *name, size_t *size)
{
    const uint8_t *data = NULL;
    uint32_t length = 0;
    if (strcmp(name, "v3_image.bin") == 0 && v3_image_bin)
    {
        data = v3_image_bin;
        length = v3_image_bin_size;
    }
    else if (strcmp(name, "v1_image.bin") == 0 && v1_image_bin)
    {
        data = v1_image_bin;
        length = v1_image_bin_size;
    }
    if (!data)
    {
        return NULL;
    }
    uint8_t *copy = malloc(length);
    if (copy)
    {
        memcpy(copy, data, length);
        *size = length;
    }
    return copy;
}

/* --- log ----------------------------------------------------------------------------------- */

static FILE *log_file;
static pthread_mutex_t log_lock = PTHREAD_MUTEX_INITIALIZER;

void shell_log_open(const char *name)
{
    char path[384];
    snprintf(path, sizeof path, "%s/%s", folder, name);
    log_file = fopen(path, "w");
}

void shell_log(const char *line)
{
    pthread_mutex_lock(&log_lock);
    printf("%s\n", line);
    if (log_file)
    {
        fprintf(log_file, "%s\n", line);
        fflush(log_file);
    }
    pthread_mutex_unlock(&log_lock);
}

/* --- the end ------------------------------------------------------------------------------- */

static volatile int finished, system_quit, game_running;
static char error[512];
static volatile int has_error;

int common_finished(void)
{
    return finished;
}

const char *common_error(void)
{
    return has_error ? error : NULL;
}

/* The error on the launcher's canvas: the title in pink, the text wrapped below. */
const uint32_t *common_error_canvas(void)
{
    gfx_gradient(0, 0, GFX_WIDTH, GFX_HEIGHT, 0xff0b1830u, 0xff1c1030u);
    const int x = 40, w = GFX_WIDTH - 80;
    char title[96];
    snprintf(title, sizeof title, "%s stopped",
             common_options.game ? common_options.game->title : "Vertrix");
    gfx_text_shadow(x, 60, title, 2, 0xffff6fb5u);
    const char *text = error;
    const int columns = w / 8;
    int y = 120;
    while (*text && y < GFX_HEIGHT - 80)
    {
        int n = (int)strlen(text);
        if (n > columns)
        {
            n = columns;
            while (n > 0 && text[n] != ' ')
            {
                --n;
            }
            n = n > 0 ? n : columns;
        }
        char line[96];
        snprintf(line, sizeof line, "%.*s", n, text);
        gfx_text(x, y, line, 1, 0xfff4f4f8u);
        text += n;
        text += *text == ' ';
        y += 20;
    }
    gfx_text(x, GFX_HEIGHT - 60, "Press any button.", 1, 0xffa8b4c8u);
    return gfx_canvas();
}

_Noreturn void shell_fatal(const char *message)
{
    char line[600];
    snprintf(line, sizeof line, "FATAL: %s", message);
    shell_log(line);
    snprintf(error, sizeof error, "%s", message);
    has_error = 1;
    finished = 1;
    if (!game_running)
    {
        shell_run(NULL); /* on the main thread, before the game: show it here */
    }
    for (;;)
    {
        sleep(1); /* the main thread shows the error and ends the app */
    }
}

_Noreturn void shell_exit(int code)
{
    char line[64];
    snprintf(line, sizeof line, "exit %d", code);
    shell_log(line);
    finished = 1;
    for (;;)
    {
        sleep(1);
    }
}

void common_request_quit(void)
{
    system_quit = 1;
}

/* Set by console_chain's callers: the launcher chose a game. */
static int chained;

void common_finish(void)
{
    if (log_file)
    {
        fclose(log_file);
        log_file = NULL;
    }
    if (common_options.game && !system_quit && !chained)
    {
        console_chain(console_launcher_path(), "back");
    }
    console_finish(system_quit);
}

/* The launcher's start of a game (consoles/launcher_shell.c). */
int common_chain(const char *path, const char *argument)
{
    chained = console_chain(path, argument);
    return chained;
}

/* --- the game's thread --------------------------------------------------------------------- */

static void (*game_main)(void);

static void *game_thread(void *unused)
{
    (void)unused;
    game_main();
    shell_exit(0);
}

void common_start_game(void (*game)(void))
{
    game_main = game;
    game_running = 1;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setstacksize(&attr, 4u << 20);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    pthread_t thread;
    if (pthread_create(&thread, &attr, game_thread, NULL) != 0)
    {
        snprintf(error, sizeof error, "The game's thread could not start.");
        has_error = 1;
        finished = 1;
    }
    pthread_attr_destroy(&attr);
}

/* --- frames -------------------------------------------------------------------------------- */

static pthread_mutex_t frame_lock = PTHREAD_MUTEX_INITIALIZER;
static uint32_t *frame_pixels;
static unsigned frame_width, frame_height;
static int frame_new;
static void (*refresh_hook)(void);

void shell_present(const uint32_t *pixels, unsigned width, unsigned height)
{
    pthread_mutex_lock(&frame_lock);
    if (width != frame_width || height != frame_height || !frame_pixels)
    {
        free(frame_pixels);
        frame_pixels = malloc((size_t)width * height * 4u);
        frame_width = frame_pixels ? width : 0;
        frame_height = frame_pixels ? height : 0;
    }
    if (frame_pixels)
    {
        memcpy(frame_pixels, pixels, (size_t)width * height * 4u);
        frame_new = 1;
    }
    pthread_mutex_unlock(&frame_lock);
}

void shell_set_refresh(void (*refresh)(void))
{
    refresh_hook = refresh;
}

void common_show(void (*show)(const uint32_t *pixels, unsigned width, unsigned height, int fresh))
{
    if (refresh_hook && !finished)
    {
        refresh_hook();
    }
    pthread_mutex_lock(&frame_lock);
    if (frame_pixels)
    {
        show(frame_pixels, frame_width, frame_height, frame_new);
        frame_new = 0;
    }
    pthread_mutex_unlock(&frame_lock);
}

void shell_wait_frame(void)
{
    static uint64_t next;
    const uint64_t period = 1000000u / 60u;
    const uint64_t now = console_microseconds();
    if (next == 0 || now > next + 4 * period)
    {
        next = now; /* late by frames (a pause, a slow load): start again from now */
    }
    next += period;
    if (next > now)
    {
        usleep((useconds_t)(next - now));
    }
}

/* --- input --------------------------------------------------------------------------------- */

enum
{
    QUEUE = 256
};
static ShellInput queue[QUEUE];
static unsigned queue_head, queue_tail;
static pthread_mutex_t input_lock = PTHREAD_MUTEX_INITIALIZER;
static volatile uint32_t pad_state[2];
static volatile int pointer_x, pointer_y, pointer_inside, quit_asked;

static void push_input(int kind, unsigned code, int down)
{
    pthread_mutex_lock(&input_lock);
    if (queue_tail - queue_head < QUEUE)
    {
        queue[queue_tail++ % QUEUE] = (ShellInput){kind, code, down, 0};
    }
    pthread_mutex_unlock(&input_lock);
}

void common_key(unsigned scan_code, int down)
{
    push_input(SHELL_KEY, scan_code, down);
}

int shell_input(ShellInput *input)
{
    pthread_mutex_lock(&input_lock);
    const int got = queue_head != queue_tail;
    if (got)
    {
        *input = queue[queue_head++ % QUEUE];
    }
    pthread_mutex_unlock(&input_lock);
    return got;
}

#ifdef SHELL_SCRIPT
/* Debug builds for the emulators: SHELL_SCRIPT is "SECONDS BUTTON; ..." with BUTTON one of up
 * down left right a b x y menu options l r (the shell's positions: a is the bottom face button)
 * or quit; each is held for a fifth of a second, from SECONDS after the start. */
static uint32_t scripted(void)
{
    static const struct
    {
        const char *name;
        uint32_t button;
    } names[] = {{"up", SHELL_PAD_UP},
                 {"down", SHELL_PAD_DOWN},
                 {"left", SHELL_PAD_LEFT},
                 {"right", SHELL_PAD_RIGHT},
                 {"a", SHELL_PAD_A},
                 {"b", SHELL_PAD_B},
                 {"x", SHELL_PAD_X},
                 {"y", SHELL_PAD_Y},
                 {"menu", SHELL_PAD_MENU},
                 {"options", SHELL_PAD_OPTIONS},
                 {"l", SHELL_PAD_SHOULDER_L},
                 {"r", SHELL_PAD_SHOULDER_R},
                 {"quit", SHELL_PAD_MENU | SHELL_PAD_OPTIONS}};
    static const char *next = SHELL_SCRIPT;
    static uint64_t start, until;
    static uint32_t held;
    const uint64_t now = console_microseconds();
    start = start ? start : now;
    if (held && now >= until)
    {
        held = 0;
    }
    double at;
    char word[16];
    int used;
    while (!held && next && sscanf(next, " %lf %15[^; ] %n", &at, word, &used) == 2 &&
           now - start >= (uint64_t)(at * 1e6))
    {
        next += used;
        next += *next == ';';
        for (unsigned i = 0; i < sizeof names / sizeof names[0]; ++i)
        {
            held |= strcmp(word, names[i].name) == 0 ? names[i].button : 0;
        }
        until = now + 200000u;
        char line[48];
        snprintf(line, sizeof line, "script: %s", word);
        shell_log(line);
    }
    return held;
}
#endif

void common_input(const uint32_t pads_in[2], int touched, int inside, int x, int y)
{
    static int touching;
    uint32_t pads[2] = {pads_in[0], pads_in[1]};
#ifdef SHELL_SCRIPT
    pads[0] |= scripted();
#endif
    pad_state[0] = pads[0];
    pad_state[1] = pads[1];
    const uint32_t both = SHELL_PAD_MENU | SHELL_PAD_OPTIONS;
    if ((pads[0] & both) == both)
    {
        quit_asked = 1;
    }
    /* The touch screen is the mouse: where it is touched, and its left button while touched. */
    if (touched && inside)
    {
        pointer_x = x;
        pointer_y = y;
        pointer_inside = 1;
    }
    if (touched && inside && !touching)
    {
        touching = 1;
        push_input(SHELL_BUTTON, 0, 1);
    }
    else if (!touched && touching)
    {
        touching = 0;
        push_input(SHELL_BUTTON, 0, 0);
    }
    if (!touched)
    {
        pointer_inside = 0;
    }
}

int shell_pointer(int *x, int *y)
{
    *x = pointer_x;
    *y = pointer_y;
    return pointer_inside;
}

uint32_t shell_pad(unsigned player)
{
    return player < 2 ? pad_state[player] : 0;
}

int shell_quit_requested(void)
{
    return quit_asked || system_quit;
}

/* --- sound --------------------------------------------------------------------------------- */

enum
{
    RING = 1u << 17 /* samples: about 1.4 s of 48 kHz stereo */
};
static int16_t ring[RING];
static uint64_t ring_written, ring_read; /* in samples, under audio_lock */
static pthread_mutex_t audio_lock = PTHREAD_MUTEX_INITIALIZER;
static uint32_t audio_rate, audio_channels, audio_bits;
static uint32_t step_fraction; /* where the mix is between two source frames, 16.16 */
static volatile int audio_paused;

void shell_audio_open(uint32_t rate, uint32_t channels, uint32_t bits)
{
    pthread_mutex_lock(&audio_lock);
    ring_read = ring_written = 0;
    step_fraction = 0;
    audio_rate = rate;
    audio_channels = channels == 2 ? 2 : 1;
    audio_bits = bits;
    pthread_mutex_unlock(&audio_lock);
}

void shell_audio_write(const uint8_t *samples, uint32_t bytes)
{
    if (!audio_bits)
    {
        return;
    }
    const uint32_t size = audio_bits == 8 ? 1u : 2u;
    uint32_t count = bytes / size;
    /* Wait for room (the game queues only a few buffers ahead); after a second, drop. */
    for (int tries = 0; tries < 500; ++tries)
    {
        pthread_mutex_lock(&audio_lock);
        const uint64_t room = RING - (ring_written - ring_read);
        pthread_mutex_unlock(&audio_lock);
        if (room >= count)
        {
            break;
        }
        usleep(2000);
    }
    pthread_mutex_lock(&audio_lock);
    const uint64_t room = RING - (ring_written - ring_read);
    count = count > room ? (uint32_t)room : count;
    const uint64_t at = ring_written;
    for (uint32_t i = 0; i < count; ++i)
    {
        ring[(at + i) % RING] = size == 1 ? (int16_t)((samples[i] - 128) << 8)
                                          : (int16_t)(samples[2 * i] | samples[2 * i + 1] << 8);
    }
    ring_written = at + count;
    pthread_mutex_unlock(&audio_lock);
}

uint64_t shell_audio_played(void)
{
    pthread_mutex_lock(&audio_lock);
    const uint64_t played = ring_read * (audio_bits == 8 ? 1u : 2u);
    pthread_mutex_unlock(&audio_lock);
    return played;
}

uint32_t shell_audio_queued(void)
{
    pthread_mutex_lock(&audio_lock);
    const uint32_t queued = (uint32_t)(ring_written - ring_read) * (audio_bits == 8 ? 1u : 2u);
    pthread_mutex_unlock(&audio_lock);
    return queued;
}

void common_audio_pause(int paused)
{
    audio_paused = paused;
}

/* Nearest-sample resampling to the system's rate: the games' streams are 11 to 44 kHz. */
void common_audio_mix(int16_t *out, unsigned frames, unsigned rate)
{
    pthread_mutex_lock(&audio_lock);
    const uint32_t channels = audio_channels ? audio_channels : 1;
    const uint32_t step = audio_rate && rate ? (uint32_t)(((uint64_t)audio_rate << 16) / rate) : 0;
    for (unsigned i = 0; i < frames; ++i)
    {
        if (audio_paused || !step || ring_written - ring_read < channels)
        {
            out[2 * i] = out[2 * i + 1] = 0;
            continue;
        }
        const int16_t left = ring[ring_read % RING];
        const int16_t right = channels == 2 ? ring[(ring_read + 1) % RING] : left;
        out[2 * i] = left;
        out[2 * i + 1] = right;
        step_fraction += step;
        uint64_t advance = (uint64_t)(step_fraction >> 16) * channels;
        step_fraction &= 0xffffu;
        const uint64_t available = (ring_written - ring_read) / channels * channels;
        ring_read += advance < available ? advance : available;
    }
    pthread_mutex_unlock(&audio_lock);
}
