/* The build machine's driver for the recompiled VERTRIX.EXE: the game's directory is a host
 * folder, frames are written as PPM files, the sound as a WAV file, and keys come from a
 * timed script.
 *
 * v1_host IMAGE GAME_DIR OUT_DIR [seconds] [frame_every] [arguments...]
 *
 * V1_SCRIPT="2 key 1c 1; 2.1 key 1c 0" presses and releases keys at guest seconds (set 1 scan
 * codes in hex; 0x1xx for the E0 prefix). V1_TRACE=1 logs every host function call;
 * V1_WATCH=hex logs each entry of a function. */

#include "dos.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

static const char *out_dir;
static double run_seconds = 30.0;
static unsigned frame_every = 35;
static unsigned long retraces;
static FILE *wav;
static uint32_t wav_bytes, wav_rate;
static FILE *log_file;

typedef struct
{
    double at;
    unsigned scan;
    int down;
} Step;

static Step script[256];
static unsigned script_count, script_next;

uint64_t v3_microseconds(void)
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint64_t)ts.tv_sec * 1000000u + (uint64_t)ts.tv_nsec / 1000u;
}

void v3_sleep_ms(uint32_t ms)
{
    usleep(ms * 1000u);
}

void v3_log(const char *format, ...)
{
    va_list args;
    char text[1024];
    va_start(args, format);
    vsnprintf(text, sizeof text, format, args);
    va_end(args);
    fprintf(stderr, "[%8.3f] %s\n", v1_clock() / 1e6, text);
    if (log_file)
    {
        fprintf(log_file, "[%8.3f] %s\n", v1_clock() / 1e6, text);
        fflush(log_file);
    }
}

_Noreturn void v3_fatal(const char *format, ...)
{
    va_list args;
    char text[1024];
    va_start(args, format);
    vsnprintf(text, sizeof text, format, args);
    va_end(args);
    v3_log("fatal: %s", text);
    exit(2);
}

static void write_frame(void)
{
    static uint32_t pixels[640 * 480];
    uint32_t w, h;
    if (!v1_vga_render(pixels, &w, &h))
    {
        return;
    }
    char path[512];
    snprintf(path, sizeof path, "%s/frame_%06lu.ppm", out_dir, retraces);
    FILE *f = fopen(path, "wb");
    if (!f)
    {
        return;
    }
    fprintf(f, "P6\n%u %u\n255\n", w, h);
    for (uint32_t i = 0; i < w * h; ++i)
    {
        const uint8_t rgb[3] = {(uint8_t)(pixels[i] >> 16), (uint8_t)(pixels[i] >> 8),
                                (uint8_t)pixels[i]};
        fwrite(rgb, 1, 3, f);
    }
    fclose(f);
}

static void retrace(void)
{
    ++retraces;
    if (frame_every && retraces % frame_every == 0)
    {
        write_frame();
    }
}

static int poll_host(void)
{
    const double now = v1_clock() / 1e6;
    while (script_next < script_count && script[script_next].at <= now)
    {
        v1_key(script[script_next].scan, script[script_next].down);
        ++script_next;
    }
    return now >= run_seconds;
}

static void wav_header(void)
{
    uint8_t h[44];
    memcpy(h, "RIFF", 4);
    const uint32_t riff = 36 + wav_bytes;
    memcpy(h + 4, &riff, 4);
    memcpy(h + 8, "WAVEfmt ", 8);
    const uint32_t fmt_size = 16;
    memcpy(h + 16, &fmt_size, 4);
    const uint16_t pcm = 1, channels = 1, align = 1, bits = 8;
    memcpy(h + 20, &pcm, 2);
    memcpy(h + 22, &channels, 2);
    memcpy(h + 24, &wav_rate, 4);
    memcpy(h + 28, &wav_rate, 4);
    memcpy(h + 32, &align, 2);
    memcpy(h + 34, &bits, 2);
    memcpy(h + 36, "data", 4);
    memcpy(h + 40, &wav_bytes, 4);
    fseek(wav, 0, SEEK_SET);
    fwrite(h, 1, sizeof h, wav);
    fseek(wav, 0, SEEK_END);
}

static void audio(const uint8_t *samples, uint32_t count, uint32_t rate)
{
    if (!wav)
    {
        char path[512];
        snprintf(path, sizeof path, "%s/sound.wav", out_dir);
        wav = fopen(path, "wb");
        if (!wav)
        {
            return;
        }
        wav_rate = rate;
        wav_header();
    }
    if (rate != wav_rate)
    {
        v1_log_once("sound rate %u Hz (the WAV file is at %u Hz)", rate, wav_rate);
    }
    fwrite(samples, 1, count, wav);
    wav_bytes += count;
}

static void console(const char *text, size_t length)
{
    v3_log("console: %.*s", (int)length, text);
}

static void read_script(const char *text)
{
    while (text && *text && script_count < 256)
    {
        double at;
        unsigned scan;
        int down;
        int used = 0;
        if (sscanf(text, " %lf key %x %d%n", &at, &scan, &down, &used) == 3)
        {
            script[script_count++] = (Step){at, scan, down};
        }
        const char *semi = strchr(text, ';');
        text = semi ? semi + 1 : NULL;
    }
}

int main(int argc, char **argv)
{
    if (argc < 4)
    {
        fprintf(stderr, "usage: %s IMAGE GAME_DIR OUT_DIR [seconds] [frame_every] [args...]\n",
                argv[0]);
        return 1;
    }
    FILE *f = fopen(argv[1], "rb");
    if (!f)
    {
        perror(argv[1]);
        return 1;
    }
    static uint8_t image[0x100000];
    const size_t size = fread(image, 1, sizeof image, f);
    fclose(f);
    if (size != v1_image.size)
    {
        fprintf(stderr, "%s: %zu bytes, the generated code expects %u\n", argv[1], size,
                v1_image.size);
        return 1;
    }
    out_dir = argv[3];
    if (argc > 4)
    {
        run_seconds = atof(argv[4]);
    }
    if (argc > 5)
    {
        frame_every = (unsigned)atoi(argv[5]);
    }
    char arguments[256] = "";
    for (int i = 6; i < argc; ++i)
    {
        const size_t n = strlen(arguments);
        snprintf(arguments + n, sizeof arguments - n, "%s%s", n ? " " : "", argv[i]);
    }
    char log_path[512];
    snprintf(log_path, sizeof log_path, "%s/vertrix.log", out_dir);
    log_file = fopen(log_path, "w");
    read_script(getenv("V1_SCRIPT"));
    if (getenv("V1_TRACE"))
    {
        v3_trace_calls = 1;
    }
    if (getenv("V1_WATCH"))
    {
        extern uint32_t v3_watch;
        v3_watch = (uint32_t)strtoul(getenv("V1_WATCH"), NULL, 16);
    }
    static const V1Platform platform = {
        .retrace = retrace, .poll = poll_host, .audio = audio, .console = console};
    V1Platform p = platform;
    p.directory = argv[2];
    p.arguments = arguments;
    const int code = v1_run(image, &p);
    v3_log("exit code %d after %lu retraces", code, retraces);
    if (wav)
    {
        wav_header();
        fclose(wav);
    }
    return code < 0 ? 0 : code;
}
