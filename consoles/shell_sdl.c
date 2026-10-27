/* The shell on the Switch and the Wii U (shell/shell.h), through SDL 2: the picture on the TV
 * (and the Wii U GamePad, which SDL mirrors) at the game's shape, as large as fits; the sound
 * stream at 48 kHz; a USB keyboard as the PC's. The controllers and the touch screen come from
 * the system itself (system_switch.c, system_wiiu.c), and so does starting the next program. */
#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include "console.h"
#include "gfx.h"
#include "shell_common.h"

enum
{
    AUDIO_RATE = 48000
};

static SDL_Window *window;
static SDL_Renderer *renderer;
static SDL_Texture *texture;
static unsigned texture_width, texture_height;
static int screen_width = 1280, screen_height = 720;
static SDL_Rect picture;
static SDL_AudioDeviceID audio_device;

static void audio_callback(void *unused, Uint8 *stream, int length)
{
    (void)unused;
    common_audio_mix((int16_t *)stream, (unsigned)length / 4u, AUDIO_RATE);
}

const char *shell_start(int argc, char **argv, const ShellOptions *options)
{
    console_init();
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
    {
        printf("SDL: %s\n", SDL_GetError());
    }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
#ifdef VERTRIX_DESKTOP
    /* A window of the game's own shape, which the player can resize or take full screen. */
    screen_width = 960;
    screen_height = 720;
    window = SDL_CreateWindow("Vertrix", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              screen_width, screen_height, SDL_WINDOW_RESIZABLE);
#else
    window = SDL_CreateWindow("Vertrix", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              screen_width, screen_height, 0);
#endif
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer)
    {
        SDL_GetRendererOutputSize(renderer, &screen_width, &screen_height);
    }
    SDL_AudioSpec want = {0}, have;
    want.freq = AUDIO_RATE;
    want.format = AUDIO_S16SYS;
    want.channels = 2;
    want.samples = 1024;
    want.callback = audio_callback;
    audio_device = SDL_OpenAudioDevice(NULL, 0, &want, &have, 0);
    const char *folder = common_start(argc, argv, options);
#ifdef VERTRIX_DESKTOP
    if (window && options->game)
    {
        SDL_SetWindowTitle(window, options->game->title);
    }
    if (options->hide_cursor)
    {
        SDL_ShowCursor(SDL_DISABLE); /* the game draws its own */
    }
#endif
    return folder;
}

/* --- the screen ---------------------------------------------------------------------------- */

/* Under the frame's lock: the picture into the texture, and where it goes on the screen. The
 * pictures' top bytes are not alpha (the games and the launcher's canvas leave them 0), so the
 * texture has none. */
static void show(const uint32_t *pixels, unsigned width, unsigned height, int fresh)
{
#ifdef VERTRIX_DESKTOP
    if (renderer)
    {
        SDL_GetRendererOutputSize(renderer, &screen_width, &screen_height);
    }
#endif
    if (!texture || width != texture_width || height != texture_height)
    {
        if (texture)
        {
            SDL_DestroyTexture(texture);
        }
        texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_STREAMING,
                                    (int)width, (int)height);
        texture_width = width;
        texture_height = height;
        fresh = 1;
        char line[160];
        snprintf(line, sizeof line, "screen %dx%d, picture %ux%u%s%s", screen_width, screen_height,
                 width, height, texture ? "" : ": ", texture ? "" : SDL_GetError());
        shell_log(line);
    }
    if (fresh && texture)
    {
        SDL_UpdateTexture(texture, NULL, pixels, (int)width * 4);
    }
    const double aspect =
        common_options.aspect > 0 ? common_options.aspect : (double)width / (double)height;
    int h = screen_height, w = (int)(h * aspect + 0.5);
    if (w > screen_width)
    {
        w = screen_width;
        h = (int)(w / aspect + 0.5);
    }
    picture = (SDL_Rect){(screen_width - w) / 2, (screen_height - h) / 2, w, h};
}

static void draw(void)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    if (common_error())
    {
        show(common_error_canvas(), GFX_WIDTH, GFX_HEIGHT, 1);
    }
    else
    {
        common_show(show);
    }
    if (texture)
    {
        SDL_RenderCopy(renderer, texture, NULL, &picture);
    }
    SDL_RenderPresent(renderer);
}

/* --- input --------------------------------------------------------------------------------- */

/* USB HID usages (SDL's scan codes) to the PC's set 1 scan codes (0x100: the E0 prefix). */
static unsigned set1(SDL_Scancode usage)
{
    static const uint8_t letters[26] = {0x1e, 0x30, 0x2e, 0x20, 0x12, 0x21, 0x22, 0x23, 0x17,
                                        0x24, 0x25, 0x26, 0x32, 0x31, 0x18, 0x19, 0x10, 0x13,
                                        0x1f, 0x14, 0x16, 0x2f, 0x11, 0x2d, 0x15, 0x2c};
    /* 40..57: Enter, Escape, Backspace, Tab, Space, - = [ ] \ (non-US #) ; ' ` , . / CapsLock */
    static const uint8_t keys[18] = {0x1c, 0x01, 0x0e, 0x0f, 0x39, 0x0c, 0x0d, 0x1a, 0x1b,
                                     0x2b, 0x2b, 0x27, 0x28, 0x29, 0x33, 0x34, 0x35, 0x3a};
    /* 73..82: Insert, Home, Page Up, Delete, End, Page Down, Right, Left, Down, Up */
    static const uint16_t moves[10] = {0x152, 0x147, 0x149, 0x153, 0x14f,
                                       0x151, 0x14d, 0x14b, 0x150, 0x148};
    if (usage >= SDL_SCANCODE_A && usage <= SDL_SCANCODE_Z)
    {
        return letters[usage - SDL_SCANCODE_A];
    }
    if (usage >= SDL_SCANCODE_1 && usage <= SDL_SCANCODE_0)
    {
        return 0x02 + (unsigned)(usage - SDL_SCANCODE_1);
    }
    if (usage >= SDL_SCANCODE_RETURN && usage <= SDL_SCANCODE_CAPSLOCK)
    {
        return keys[usage - SDL_SCANCODE_RETURN];
    }
    if (usage >= SDL_SCANCODE_F1 && usage <= SDL_SCANCODE_F10)
    {
        return 0x3b + (unsigned)(usage - SDL_SCANCODE_F1);
    }
    if (usage >= SDL_SCANCODE_INSERT && usage <= SDL_SCANCODE_UP)
    {
        return moves[usage - SDL_SCANCODE_INSERT];
    }
    switch (usage)
    {
        case SDL_SCANCODE_F11:
            return 0x57;
        case SDL_SCANCODE_F12:
            return 0x58;
        case SDL_SCANCODE_LCTRL:
            return 0x1d;
        case SDL_SCANCODE_LSHIFT:
            return 0x2a;
        case SDL_SCANCODE_LALT:
            return 0x38;
        case SDL_SCANCODE_RCTRL:
            return 0x11d;
        case SDL_SCANCODE_RSHIFT:
            return 0x36;
        case SDL_SCANCODE_RALT:
            return 0x138;
        default:
            return 0;
    }
}

/* Events, controllers and the touch screen; returns player 1's buttons. */
static uint32_t input(void)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            common_request_quit();
        }
#ifdef VERTRIX_DESKTOP
        else if (event.type == SDL_KEYDOWN && !event.key.repeat &&
                 event.key.keysym.scancode == SDL_SCANCODE_F11)
        {
            SDL_SetWindowFullscreen(window, (SDL_GetWindowFlags(window) & SDL_WINDOW_FULLSCREEN_DESKTOP)
                                                ? 0
                                                : SDL_WINDOW_FULLSCREEN_DESKTOP);
        }
#endif
        else if ((event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) && !event.key.repeat)
        {
            const unsigned code = set1(event.key.keysym.scancode);
            if (code)
            {
                common_key(code, event.type == SDL_KEYDOWN);
            }
        }
    }
    uint32_t pads[2];
    int touched, tx, ty;
    console_read_input(pads, &touched, &tx, &ty);
    int inside = 0, x = 0, y = 0;
    if (touched && picture.w > 0 && picture.h > 0)
    {
        inside = tx >= picture.x && tx < picture.x + picture.w && ty >= picture.y &&
                 ty < picture.y + picture.h;
        x = (int)((int64_t)(tx - picture.x) * (int64_t)texture_width / picture.w);
        y = (int)((int64_t)(ty - picture.y) * (int64_t)texture_height / picture.h);
    }
    common_input(pads, touched, inside, x, y);
#ifdef VERTRIX_DESKTOP
    {
        /* The mouse: over the picture (hovering counts) and its buttons. */
        int mx, my;
        const Uint32 buttons = SDL_GetMouseState(&mx, &my);
        int over = 0, px = 0, py = 0;
        if (picture.w > 0 && picture.h > 0 && (SDL_GetWindowFlags(window) & SDL_WINDOW_MOUSE_FOCUS))
        {
            over = mx >= picture.x && mx < picture.x + picture.w && my >= picture.y &&
                   my < picture.y + picture.h;
            px = (int)((int64_t)(mx - picture.x) * (int64_t)texture_width / picture.w);
            py = (int)((int64_t)(my - picture.y) * (int64_t)texture_height / picture.h);
        }
        common_mouse(over, px, py,
                     ((buttons & SDL_BUTTON_LMASK) ? 1u : 0u) | ((buttons & SDL_BUTTON_RMASK) ? 2u : 0u) |
                         ((buttons & SDL_BUTTON_MMASK) ? 4u : 0u));
    }
#endif
    return pads[0];
}

/* --- the main loop ------------------------------------------------------------------------- */

_Noreturn void shell_run(void (*game)(void))
{
    if (!renderer || !audio_device)
    {
        char line[160];
        snprintf(line, sizeof line, "SDL: %s%s%s", renderer ? "" : "no renderer; ",
                 audio_device ? "" : "no sound; ", SDL_GetError());
        shell_log(line);
    }
    if (game)
    {
        common_start_game(game);
    }
    if (audio_device)
    {
        SDL_PauseAudioDevice(audio_device, 0);
    }
    uint32_t before = ~0u;
    for (;;)
    {
        const uint32_t pads = input();
        if (common_finished())
        {
            /* An error stays until a button is pressed (or the system closes the app). */
            if (!common_error() || shell_quit_requested() || (pads & ~before))
            {
                break;
            }
        }
        before = pads;
        draw();
    }
    if (audio_device)
    {
        SDL_CloseAudioDevice(audio_device);
    }
    common_finish();
    SDL_Quit();
    exit(0);
}
