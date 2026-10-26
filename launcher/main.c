/* The Vertrix launcher: one Homebrew Channel app (sd:/apps/vertrix/) that starts each of the
 * four ported games and plays the soundtrack (launcher/README.md).
 *
 *   sd:/apps/vertrix/boot.dol         this launcher (packed by dolxz)
 *   sd:/apps/vertrix/games/NAME.dol   the games (packed by dolxz)
 *   sd:/apps/vertrix/<game folder>/   each game's original files
 *   sd:/apps/vertrix/music/<album>/   MP3 files
 *
 * A game starts with its data folder and this DOL's path as arguments (launcher/app.h) and
 * comes back here when it ends. The Switch, Wii U and 3DS builds compile this file unchanged
 * against consoles/compat/, with their own folder, programs and button names
 * (consoles/README.md). */
#include <asndlib.h>
#include <fat.h>
#include <gccore.h>
#include <mp3player.h>
#include <ogc/lwp_watchdog.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <wiiuse/wpad.h>

#include "app.h"
#include "gfx.h"
#include "input_wii.h"
#include "logo.h"
#include "music.h"
#include "wiiupdate.h"

#ifndef APP_VERSION
#define APP_VERSION "0"
#endif

/* What a console's build sets otherwise (consoles/compat/launcher_compat.h). */
#ifndef LAUNCHER_HOME
#define LAUNCHER_HOME "sd:/apps/vertrix"
#define LAUNCHER_PROGRAM_EXTENSION ".dol"
#define LAUNCHER_HINT_EXIT "HOME: Exit"
#define LAUNCHER_HINT_MUSIC "A: Play  2: Pause  -/+: Prev/Next  1: Shuffle  B: Back"
#define LAUNCHER_NOT_A_PROGRAM "%s could not be read, or is not a Wii program."
#else
#define LAUNCHER_NOT_A_PROGRAM "%s could not be started: start Vertrix from the homebrew menu."
#endif

typedef struct
{
    const char *title;
    const char *year;
    const char *about;
    const char *folder; /* its files, in the app folder */
    const char *dol;    /* in games/, with LAUNCHER_PROGRAM_EXTENSION */
    const char *needs;  /* a file that must be in the folder */
    const char *needs_text;
} Game;

static const Game games[] = {
    {"Vertrix", "1997", "The original, for DOS", "vertrix1", "vertrix1", "BIN1.BIN",
     "the whole original release (VERTRIX.EXE, BIN1.BIN, BIN2.BIN and the rest)"},
    {"Vertrix 2 v1.2", "2001", "The first Windows release", "vertrix2-v12", "vertrix2-v12",
     "Vertrix2.vf", "Vertrix2.vf from Vertrix 2 v1.2"},
    {"Vertrix 2", "2003", "Version 2.0", "vertrix2", "vertrix2", "Vertrix2.vf",
     "Vertrix2.vf from Vertrix 2 v2.0"},
    {"Vertrix 3", "2009", "In 3D", "vertrix3", "vertrix3", "VERTRIX3.VF",
     "VERTRIX3.VF from Vertrix 3"},
};
enum
{
    GAME_COUNT = sizeof games / sizeof games[0],
    ITEM_MUSIC = GAME_COUNT,
    ITEM_COUNT = GAME_COUNT + 1
};

/* Colours, after the logo's teal stripes and pink letters. */
enum
{
    TEXT = 0xfff4f4f8u,
    TEXT_DIM = 0xffa8b4c8u,
    PINK = 0xffff6fb5u,
    TEAL = 0xff52d6d0u,
    GREEN = 0xff7ee08au,
    AMBER = 0xffffc04au,
    PANEL = 0xb0101828u,
    PANEL_HOT = 0xe0283a5au
};

static char app_folder[128];
static char launcher_path[160];
static int have_dol[GAME_COUNT], have_data[GAME_COUNT];
static int total_tracks;
static int returning; /* started again by a game: no second update check */

static enum { SCREEN_MAIN, SCREEN_MUSIC } screen;
static int selected;
static int album_shown, track_selected, track_top;

static struct
{
    int open;
    char title[64];
    char text[320];
} message;

static wiiupdate_popup popup;
static int popup_state;

/* --- files -------------------------------------------------------------------------------- */

static int exists(const char *path)
{
    struct stat info;
    return stat(path, &info) == 0;
}

static void check_games(void)
{
    char path[256];
    for (int i = 0; i < GAME_COUNT; ++i)
    {
        snprintf(path, sizeof path, "%s/games/%s%s", app_folder, games[i].dol,
                 LAUNCHER_PROGRAM_EXTENSION);
        have_dol[i] = exists(path);
        snprintf(path, sizeof path, "%s/%s/%s", app_folder, games[i].folder, games[i].needs);
        have_data[i] = exists(path);
    }
}

static void load_settings(void)
{
    char path[192], line[64];
    snprintf(path, sizeof path, "%s/launcher.cfg", app_folder);
    FILE *file = fopen(path, "r");
    if (file == NULL)
    {
        return;
    }
    while (fgets(line, sizeof line, file) != NULL)
    {
        int value;
        if (sscanf(line, "selected %d", &value) == 1 && value >= 0 && value < ITEM_COUNT)
        {
            selected = value;
        }
        else if (sscanf(line, "shuffle %d", &value) == 1)
        {
            music_set_shuffle(value != 0);
        }
        else if (sscanf(line, "volume %d", &value) == 1)
        {
            music_set_volume(value);
        }
    }
    fclose(file);
}

static void save_settings(void)
{
    char path[192];
    snprintf(path, sizeof path, "%s/launcher.cfg", app_folder);
    FILE *file = fopen(path, "w");
    if (file != NULL)
    {
        fprintf(file, "selected %d\nshuffle %d\nvolume %d\n", selected, music_shuffle(),
                music_volume());
        fclose(file);
    }
}

/* --- input -------------------------------------------------------------------------------- */

/* Buttons pressed this frame, with Up/Down/Left/Right repeating while held. */
static uint32_t buttons(void)
{
    enum
    {
        DIRECTIONS = WPAD_BUTTON_UP | WPAD_BUTTON_DOWN | WPAD_BUTTON_LEFT | WPAD_BUTTON_RIGHT
    };
    static uint32_t held_since_frame;
    static unsigned held_frames;
    static uint32_t stick_before;
    uint32_t down = INPUT_ButtonsDown();
    uint32_t held = INPUT_ButtonsHeld() & DIRECTIONS;
    float sx, sy;
    uint32_t stick = 0;
    if (INPUT_Stick(INPUT_STICK_LEFT, &sx, &sy, NULL) > 0.6f)
    {
        if (sy > 0.6f)
        {
            stick |= WPAD_BUTTON_UP;
        }
        else if (sy < -0.6f)
        {
            stick |= WPAD_BUTTON_DOWN;
        }
        else if (sx < -0.6f)
        {
            stick |= WPAD_BUTTON_LEFT;
        }
        else if (sx > 0.6f)
        {
            stick |= WPAD_BUTTON_RIGHT;
        }
    }
    down |= stick & ~stick_before;
    stick_before = stick;
    held |= stick;
    if (held != held_since_frame)
    {
        held_since_frame = held;
        held_frames = 0;
    }
    else if (held != 0 && ++held_frames >= 24 && (held_frames - 24) % 6 == 0)
    {
        down |= held;
    }
    return down;
}

static int pointer(int *x, int *y)
{
    if (!INPUT_CursorActive())
    {
        return 0;
    }
    INPUT_CursorPosition(x, y);
    return 1;
}

/* --- drawing ------------------------------------------------------------------------------ */

static void draw_background(void)
{
    gfx_gradient(0, 0, GFX_WIDTH, GFX_HEIGHT, 0xff0b1830u, 0xff1c1030u);
    /* The logo's diagonal stripes, faint. */
    for (int y = 0; y < GFX_HEIGHT; ++y)
    {
        for (int x = (y % 48) - 48; x < GFX_WIDTH; x += 48)
        {
            gfx_fill(x, y, 16, 1, 0x0c52d6d0u);
        }
    }
    gfx_fill(0, GFX_HEIGHT - 44, GFX_WIDTH, 44, 0x80000000u);
    gfx_fill(0, GFX_HEIGHT - 44, GFX_WIDTH, 1, 0x6052d6d0u);
    gfx_save_background();
}

static void draw_cursor(void)
{
    int x, y;
    if (!pointer(&x, &y))
    {
        return;
    }
    gfx_round_box(x - 9, y - 9, 18, 18, 9, 0xc0000000u);
    gfx_round_box(x - 7, y - 7, 14, 14, 7, 0xffffffffu);
    gfx_round_box(x - 5, y - 5, 10, 10, 5, PINK);
}

static void format_time(char *out, size_t room, int seconds)
{
    snprintf(out, room, "%d:%02d", seconds / 60, seconds % 60);
}

static const MusicTrack *now_playing(void)
{
    const MusicAlbum *album = music_album(music_current_album());
    const int track = music_current_track();
    return album != NULL && track >= 0 && track < album->count ? &album->tracks[track] : NULL;
}

static void draw_hints(const char *hints)
{
    gfx_text(24, GFX_HEIGHT - 30, hints, 1, TEXT_DIM);
}

static void draw_mini_player(void)
{
    const MusicTrack *track = now_playing();
    if (track == NULL)
    {
        return;
    }
    char line[160], time[24];
    format_time(time, sizeof time, music_elapsed());
    snprintf(line, sizeof line, "%s %s  %s", music_paused() ? "II" : "\x0e", track->title, time);
    const int width = gfx_text_width(line, 1) > 300 ? 300 : gfx_text_width(line, 1);
    gfx_text_fit(GFX_WIDTH - 24 - width, GFX_HEIGHT - 30, line, 1, 300, TEAL);
}

static void draw_message(void)
{
    if (!message.open)
    {
        return;
    }
    const int w = 520, h = 190, x = (GFX_WIDTH - w) / 2, y = (GFX_HEIGHT - h) / 2;
    gfx_fill(0, 0, GFX_WIDTH, GFX_HEIGHT, 0x90000000u);
    gfx_round_box(x, y, w, h, 14, 0xf0182440u);
    gfx_frame(x, y, w, h, 14, PINK);
    gfx_text_shadow(x + 24, y + 18, message.title, 2, PINK);
    /* The text, wrapped at spaces to the box. */
    const char *text = message.text;
    const int columns = (w - 48) / 8;
    int line_y = y + 64;
    while (*text && line_y < y + h - 40)
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
        gfx_text(x + 24, line_y, line, 1, TEXT);
        text += n;
        text += *text == ' ';
        line_y += 18;
    }
    gfx_text(x + w - 24 - gfx_text_width("A: OK", 1), y + h - 30, "A: OK", 1, TEXT_DIM);
}

static void draw_popup(void)
{
    if (popup_state != WIIUPDATE_POPUP_OPEN)
    {
        return;
    }
    const int w = 540, h = 200, x = (GFX_WIDTH - w) / 2, y = (GFX_HEIGHT - h) / 2;
    gfx_fill(0, 0, GFX_WIDTH, GFX_HEIGHT, 0x90000000u);
    gfx_round_box(x, y, w, h, 14, 0xf0182440u);
    gfx_frame(x, y, w, h, 14, TEAL);
    gfx_text_shadow(x + 24, y + 18, popup.title, 2, TEAL);
    gfx_text_fit(x + 24, y + 70, popup.text, 1, w - 48, TEXT);
    gfx_text_fit(x + 24, y + 94, popup.detail, 1, w - 48, TEXT_DIM);
    if (popup.progress >= 0)
    {
        gfx_round_box(x + 24, y + 124, w - 48, 14, 7, 0xff304060u);
        gfx_round_box(x + 24, y + 124, (w - 48) * popup.progress / 100, 14, 7, GREEN);
    }
    gfx_text_fit(x + 24, y + h - 32, popup.hint, 1, w - 48, TEXT_DIM);
}

/* --- the main screen ---------------------------------------------------------------------- */

enum
{
    ITEM_X = 88,
    ITEM_W = GFX_WIDTH - 2 * ITEM_X,
    ITEM_Y = 128,
    ITEM_H = 56,
    ITEM_STEP = 62
};

static void draw_main(void)
{
    gfx_image(logo_pixels, logo_width, logo_height, (GFX_WIDTH - 256) / 2, 28, 256, 67);
    for (int i = 0; i < ITEM_COUNT; ++i)
    {
        const int y = ITEM_Y + i * ITEM_STEP;
        const int hot = i == selected && !message.open;
        gfx_round_box(ITEM_X, y, ITEM_W, ITEM_H, 12, hot ? PANEL_HOT : PANEL);
        if (hot)
        {
            gfx_frame(ITEM_X, y, ITEM_W, ITEM_H, 12, PINK);
        }
        const char *title, *about, *status;
        char line[96];
        uint32_t status_colour;
        if (i < GAME_COUNT)
        {
            title = games[i].title;
            snprintf(line, sizeof line, "%s - %s", games[i].year, games[i].about);
            about = line;
            const int ready = have_dol[i] && have_data[i];
            status = ready ? "READY" : (have_dol[i] ? "NEEDS FILES" : "NOT INSTALLED");
            status_colour = ready ? GREEN : AMBER;
        }
        else
        {
            title = "Music";
            /* Latin-1, as the text drawing expects: 0xe9 is the e of Cedric. */
            snprintf(line, sizeof line, "%d track%s by C\xe9"
                                        "dric Castel and The Clusters",
                     total_tracks, total_tracks == 1 ? "" : "s");
            if (!total_tracks)
            {
                snprintf(line, sizeof line, "No music in %s/music/ yet", app_folder);
            }
            about = line;
            status = music_playing() ? (music_paused() ? "PAUSED" : "PLAYING") : "";
            status_colour = TEAL;
        }
        gfx_text_shadow(ITEM_X + 20, y + 6, title, 2, hot ? 0xffffffffu : TEXT);
        gfx_text(ITEM_X + 20, y + 36, about, 1, hot ? TEXT : TEXT_DIM);
        gfx_text(ITEM_X + ITEM_W - 20 - gfx_text_width(status, 1), y + 14, status, 1,
                 status_colour);
    }
    draw_hints("A: Choose   " LAUNCHER_HINT_EXIT);
    draw_mini_player();
}

static void show_missing(int i)
{
    message.open = 1;
    if (!have_dol[i])
    {
        snprintf(message.title, sizeof message.title, "Not installed");
        snprintf(message.text, sizeof message.text,
                 "%s's program is missing: copy games/%s%s from the release into %s/games/.",
                 games[i].title, games[i].dol, LAUNCHER_PROGRAM_EXTENSION, app_folder);
        return;
    }
    snprintf(message.title, sizeof message.title, "Files needed");
    snprintf(message.text, sizeof message.text,
             "%s needs the original game's files. Copy %s into %s/%s/ on the SD card.",
             games[i].title, games[i].needs_text, app_folder, games[i].folder);
}

static void launch(int i)
{
    char dol[256], data[256];
    snprintf(dol, sizeof dol, "%s/games/%s%s", app_folder, games[i].dol,
             LAUNCHER_PROGRAM_EXTENSION);
    snprintf(data, sizeof data, "%s/%s", app_folder, games[i].folder);
    save_settings();
    music_stop();
    WIIUPDATE_Cancel();
    WIIUPDATE_Wait(3000);
    /* The game starts with a clean slate: no voices, no controller threads. */
    ASND_Pause(1);
    ASND_End();
    INPUT_Shutdown();
    const char *args[3] = {dol, data, launcher_path};
    vertrix_app_boot(dol, 3, args);
    /* Only when the DOL could not be read. */
    ASND_Init();
    ASND_Pause(0);
    MP3Player_Init();
    INPUT_Init();
    INPUT_SetScreenSize(GFX_WIDTH, GFX_HEIGHT);
    VIDEO_SetBlack(FALSE);
    message.open = 1;
    snprintf(message.title, sizeof message.title, "Could not start");
    snprintf(message.text, sizeof message.text, LAUNCHER_NOT_A_PROGRAM, dol);
}

static void choose(int item)
{
    if (item == ITEM_MUSIC)
    {
        screen = SCREEN_MUSIC;
        album_shown = music_current_album() >= 0 ? music_current_album() : 0;
        track_selected = music_current_track() >= 0 ? music_current_track() : 0;
        track_top = 0;
        return;
    }
    if (have_dol[item] && have_data[item])
    {
        launch(item);
    }
    else
    {
        show_missing(item);
    }
}

static void update_main(uint32_t down)
{
    int x, y;
    if (pointer(&x, &y) && INPUT_CursorMoved() && x >= ITEM_X && x < ITEM_X + ITEM_W)
    {
        for (int i = 0; i < ITEM_COUNT; ++i)
        {
            if (y >= ITEM_Y + i * ITEM_STEP && y < ITEM_Y + i * ITEM_STEP + ITEM_H)
            {
                selected = i;
            }
        }
    }
    if (down & WPAD_BUTTON_UP)
    {
        selected = (selected + ITEM_COUNT - 1) % ITEM_COUNT;
    }
    if (down & WPAD_BUTTON_DOWN)
    {
        selected = (selected + 1) % ITEM_COUNT;
    }
    if (down & (WPAD_BUTTON_A | WPAD_BUTTON_2))
    {
        choose(selected);
    }
    if (down & WPAD_BUTTON_PLUS)
    {
        music_next();
    }
    if (down & WPAD_BUTTON_MINUS)
    {
        music_previous();
    }
}

/* --- the music screen --------------------------------------------------------------------- */

enum
{
    LIST_X = 24,
    LIST_Y = 112,
    LIST_W = GFX_WIDTH - 48,
    ROW_H = 20,
    ROWS = 10
};

static void draw_visualiser(int x, int y, int w, int h)
{
    static int shown[MUSIC_BANDS];
    unsigned char levels[MUSIC_BANDS];
    music_levels(levels);
    const int bar = w / MUSIC_BANDS;
    for (int i = 0; i < MUSIC_BANDS; ++i)
    {
        const int want = music_playing() && !music_paused() ? levels[i] : 0;
        /* Up at once, down slowly. */
        shown[i] = want > shown[i] ? want : shown[i] - 12;
        shown[i] = shown[i] < 0 ? 0 : shown[i];
        const int height = shown[i] * h / 255;
        for (int k = 0; k < height; k += 3)
        {
            const uint32_t c = k * 3 < h * 2 ? TEAL : (k * 4 < h * 3 ? 0xffb090ffu : PINK);
            gfx_fill(x + i * bar, y + h - k - 2, bar - 2, 2, c);
        }
    }
}

static void draw_music(void)
{
    gfx_image(logo_pixels, logo_width, logo_height, 20, 17, 128, 34);
    gfx_text_shadow(170, 18, "Music", 2, PINK);
    const MusicAlbum *album = music_album(album_shown);
    if (album == NULL)
    {
        gfx_text(170, 52, "No albums: put MP3 folders in", 1, TEXT_DIM);
        char folder[192];
        snprintf(folder, sizeof folder, "%s/music/<album>/", app_folder);
        gfx_text(LIST_X, LIST_Y, folder, 1, TEXT);
        draw_hints("B: Back");
        return;
    }
    /* The albums as tabs. */
    int tab_x = LIST_X;
    for (int i = 0; i < music_album_count(); ++i)
    {
        const MusicAlbum *a = music_album(i);
        const int w = gfx_text_width(a->name, 1) + 24;
        gfx_round_box(tab_x, 70, w, 26, 13, i == album_shown ? PANEL_HOT : PANEL);
        if (i == album_shown)
        {
            gfx_frame(tab_x, 70, w, 26, 13, TEAL);
        }
        gfx_text(tab_x + 12, 75, a->name, 1, i == album_shown ? 0xffffffffu : TEXT_DIM);
        tab_x += w + 8;
    }
    gfx_text(GFX_WIDTH - 24 - gfx_text_width("< >", 1), 52, "< >", 1, TEXT_DIM);

    /* The tracks. */
    gfx_round_box(LIST_X - 8, LIST_Y - 6, LIST_W + 16, ROWS * ROW_H + 12, 10, PANEL);
    for (int row = 0; row < ROWS && track_top + row < album->count; ++row)
    {
        const int index = track_top + row, y = LIST_Y + row * ROW_H;
        const MusicTrack *track = &album->tracks[index];
        const int playing = album_shown == music_current_album() && index == music_current_track();
        if (index == track_selected)
        {
            gfx_round_box(LIST_X - 4, y, LIST_W + 8, ROW_H, 6, PANEL_HOT);
        }
        char number[8];
        snprintf(number, sizeof number, "%2d", track->number ? track->number : index + 1);
        gfx_text(LIST_X + 4, y + 2, playing ? "\x0e" : number, 1, playing ? PINK : TEXT_DIM);
        gfx_text_fit(LIST_X + 36, y + 2, track->title, 1, LIST_W - 44,
                     playing ? PINK : (index == track_selected ? 0xffffffffu : TEXT));
    }
    if (album->count > ROWS)
    {
        const int track_h = ROWS * ROW_H, knob = track_h * ROWS / album->count;
        const int at = (track_h - knob) * track_top / (album->count - ROWS);
        gfx_round_box(LIST_X + LIST_W + 2, LIST_Y + at, 4, knob, 2, 0x8052d6d0u);
    }

    /* Now playing. */
    const int py = LIST_Y + ROWS * ROW_H + 14;
    gfx_round_box(16, py, GFX_WIDTH - 32, GFX_HEIGHT - 50 - py, 12, PANEL);
    const MusicTrack *track = now_playing();
    if (track != NULL)
    {
        const MusicAlbum *playing = music_album(music_current_album());
        gfx_text_fit(32, py + 10, track->title, 2, 360, 0xffffffffu);
        char line[192];
        snprintf(line, sizeof line, "%s%s%s", track->artist, track->artist[0] ? " - " : "",
                 playing->name);
        gfx_text_fit(32, py + 46, line, 1, 360, TEXT_DIM);
        const int elapsed = music_elapsed(), length = music_length();
        char times[64], a[24], b[24];
        format_time(a, sizeof a, elapsed);
        format_time(b, sizeof b, length);
        snprintf(times, sizeof times, "%s / %s%s%s", a, b, music_paused() ? "  paused" : "",
                 music_shuffle() ? "  shuffle" : "");
        gfx_round_box(32, py + 70, 360, 8, 4, 0xff304060u);
        if (length > 0)
        {
            const int done = elapsed > length ? length : elapsed;
            gfx_round_box(32, py + 70, 8 + 352 * done / length, 8, 4, PINK);
        }
        gfx_text(32, py + 82, times, 1, TEXT_DIM);
    }
    else
    {
        gfx_text(32, py + 20, "Nothing playing: pick a track and press A.", 1, TEXT_DIM);
        gfx_text(32, py + 44, music_shuffle() ? "Shuffle is on." : "Shuffle is off.", 1,
                 TEXT_DIM);
    }
    draw_visualiser(GFX_WIDTH - 32 - 192, py + 10, 192, GFX_HEIGHT - 50 - py - 20);
    draw_hints(LAUNCHER_HINT_MUSIC);
}

static void keep_visible(const MusicAlbum *album)
{
    if (track_selected < track_top)
    {
        track_top = track_selected;
    }
    if (track_selected >= track_top + ROWS)
    {
        track_top = track_selected - ROWS + 1;
    }
    const int last = album->count > ROWS ? album->count - ROWS : 0;
    track_top = track_top > last ? last : (track_top < 0 ? 0 : track_top);
}

static void update_music(uint32_t down)
{
    const MusicAlbum *album = music_album(album_shown);
    if (down & (WPAD_BUTTON_B | WPAD_BUTTON_HOME))
    {
        screen = SCREEN_MAIN;
        return;
    }
    if (album == NULL)
    {
        return;
    }
    const int albums = music_album_count();
    if (down & (WPAD_BUTTON_LEFT | WPAD_BUTTON_RIGHT))
    {
        album_shown = (album_shown + (down & WPAD_BUTTON_LEFT ? albums - 1 : 1)) % albums;
        album = music_album(album_shown);
        track_selected = album_shown == music_current_album() ? music_current_track() : 0;
        track_top = 0;
    }
    if (down & WPAD_BUTTON_UP)
    {
        track_selected = (track_selected + album->count - 1) % album->count;
    }
    if (down & WPAD_BUTTON_DOWN)
    {
        track_selected = (track_selected + 1) % album->count;
    }
    int dx, dy, wheel;
    INPUT_MouseDelta(&dx, &dy, &wheel);
    if (wheel != 0)
    {
        track_top += wheel > 0 ? 3 : -3;
        const int last = album->count > ROWS ? album->count - ROWS : 0;
        track_top = track_top > last ? last : (track_top < 0 ? 0 : track_top);
    }
    else
    {
        keep_visible(album);
    }
    int x, y, pointed = -1;
    if (pointer(&x, &y))
    {
        if (x >= LIST_X && x < LIST_X + LIST_W && y >= LIST_Y && y < LIST_Y + ROWS * ROW_H &&
            track_top + (y - LIST_Y) / ROW_H < album->count)
        {
            pointed = track_top + (y - LIST_Y) / ROW_H;
            if (INPUT_CursorMoved())
            {
                track_selected = pointed;
            }
        }
        /* The album tabs. */
        int tab_x = LIST_X;
        for (int i = 0; i < albums && y >= 70 && y < 96; ++i)
        {
            const int w = gfx_text_width(music_album(i)->name, 1) + 24;
            if (x >= tab_x && x < tab_x + w && (down & WPAD_BUTTON_A))
            {
                album_shown = i;
                track_selected = track_top = 0;
                return;
            }
            tab_x += w + 8;
        }
    }
    if (down & WPAD_BUTTON_A)
    {
        if (pointed < 0 && pointer(&x, &y) && y < LIST_Y)
        {
            return; /* a click above the list, not on a tab */
        }
        music_play(album_shown, track_selected);
    }
    if (down & WPAD_BUTTON_2)
    {
        if (music_playing())
        {
            music_toggle_pause();
        }
        else
        {
            music_play(album_shown, track_selected);
        }
    }
    if (down & WPAD_BUTTON_1)
    {
        music_set_shuffle(!music_shuffle());
    }
    if (down & WPAD_BUTTON_PLUS)
    {
        music_next();
    }
    if (down & WPAD_BUTTON_MINUS)
    {
        music_previous();
    }
}

/* --- debug builds ------------------------------------------------------------------------- */

#if defined(LAUNCHER_SCRIPT) || defined(LAUNCHER_BACK_SCRIPT)
/* "SECONDS WORD; ..." where WORD is a button (up down left right a b 1 2 plus minus home) or
 * "shot", which saves the screen as APP/shots/launcherNN.ppm. LAUNCHER_SCRIPT runs on a start
 * from the loader, LAUNCHER_BACK_SCRIPT on the way back from a game. */
static uint32_t run_script(void)
{
#ifdef LAUNCHER_SCRIPT
    static char first[] = LAUNCHER_SCRIPT;
#else
    static char first[] = "";
#endif
#ifdef LAUNCHER_BACK_SCRIPT
    static char back[] = LAUNCHER_BACK_SCRIPT;
#else
    static char back[] = "";
#endif
    static const struct
    {
        const char *name;
        uint32_t button;
    } names[] = {{"up", WPAD_BUTTON_UP},       {"down", WPAD_BUTTON_DOWN},
                 {"left", WPAD_BUTTON_LEFT},   {"right", WPAD_BUTTON_RIGHT},
                 {"a", WPAD_BUTTON_A},         {"b", WPAD_BUTTON_B},
                 {"1", WPAD_BUTTON_1},         {"2", WPAD_BUTTON_2},
                 {"plus", WPAD_BUTTON_PLUS},   {"minus", WPAD_BUTTON_MINUS},
                 {"home", WPAD_BUTTON_HOME}};
    static char *next;
    static int started, shots;
    static u64 start;
    if (!started)
    {
        started = 1;
        start = gettime();
        next = returning ? back : first;
    }
    const double now = ticks_to_millisecs(gettime() - start) / 1000.0;
    uint32_t down = 0;
    while (next != NULL && *next)
    {
        double at;
        char word[16];
        int used;
        if (sscanf(next, " %lf %15[^; ] %n", &at, word, &used) < 2 || at > now)
        {
            break;
        }
        next += used;
        next += *next == ';';
        if (!strcmp(word, "shot"))
        {
            char path[192];
            snprintf(path, sizeof path, "%s/shots", app_folder);
            mkdir(path, 0777);
            snprintf(path, sizeof path, "%s/shots/launcher%02d.ppm", app_folder, shots++);
            gfx_save_ppm(path);
            printf("launcher: %s\n", path);
            continue;
        }
        for (unsigned i = 0; i < sizeof names / sizeof names[0]; ++i)
        {
            down |= strcmp(word, names[i].name) == 0 ? names[i].button : 0;
        }
    }
    return down;
}
#else
static uint32_t run_script(void)
{
    return 0;
}
#endif

/* --- start-up ----------------------------------------------------------------------------- */

/* The folder this DOL was started from (the Homebrew Channel passes it), else the default. */
static void find_app_folder(int argc, char **argv)
{
    snprintf(app_folder, sizeof app_folder, "%s", LAUNCHER_HOME);
    snprintf(launcher_path, sizeof launcher_path, "%s/boot.dol", app_folder);
    if (argc > 0 && argv[0] != NULL && strchr(argv[0], '/') != NULL &&
        (strncmp(argv[0], "sd:/", 4) == 0 || strncmp(argv[0], "usb:/", 5) == 0))
    {
        snprintf(launcher_path, sizeof launcher_path, "%s", argv[0]);
        snprintf(app_folder, sizeof app_folder, "%s", argv[0]);
        *strrchr(app_folder, '/') = 0;
    }
}

int main(int argc, char **argv)
{
#if defined(LAUNCHER_SCRIPT) || defined(LAUNCHER_BACK_SCRIPT)
    SYS_STDIO_Report(true); /* stdout into Dolphin's OSReport log */
#endif
    gfx_init();
    const int mounted = fatInitDefault();
    find_app_folder(argc, argv);
    returning = argc >= 2 && argv[1] != NULL && strcmp(argv[1], "back") == 0;
    INPUT_Init();
    INPUT_SetScreenSize(GFX_WIDTH, GFX_HEIGHT);
    ASND_Init();
    ASND_Pause(0);
    MP3Player_Init();

    draw_background();
    gfx_restore_background();
    gfx_image(logo_pixels, logo_width, logo_height, (GFX_WIDTH - 256) / 2, 28, 256, 67);
    gfx_text(ITEM_X, ITEM_Y, "Reading the SD card...", 1, TEXT_DIM);
    gfx_present();

    check_games();
    char path[192];
    snprintf(path, sizeof path, "%s/music", app_folder);
    music_scan(path);
    for (int i = 0; i < music_album_count(); ++i)
    {
        total_tracks += music_album(i)->count;
    }
    load_settings();
    printf("launcher %s: %s, card %s, %d albums, %d tracks, games %d%d%d%d, data %d%d%d%d%s\n",
           APP_VERSION, launcher_path, mounted ? "mounted" : "not mounted", music_album_count(),
           total_tracks, have_dol[0], have_dol[1], have_dol[2], have_dol[3], have_data[0],
           have_data[1], have_data[2], have_data[3], returning ? ", back from a game" : "");
    if (!returning)
    {
        WIIUPDATE_SetAppPath(launcher_path);
        WIIUPDATE_Start("quatric", "Vertrix2", APP_VERSION);
    }

    for (;;)
    {
        INPUT_Update();
        uint32_t down = buttons() | run_script();
        music_update();
        if (!returning)
        {
            popup_state = WIIUPDATE_Popup(down, &popup);
            if (popup_state == WIIUPDATE_POPUP_EXIT)
            {
                break;
            }
            if (popup_state == WIIUPDATE_POPUP_OPEN)
            {
                down = 0;
            }
        }
        if (message.open)
        {
            if (down & (WPAD_BUTTON_A | WPAD_BUTTON_B | WPAD_BUTTON_HOME))
            {
                message.open = 0;
            }
            down = 0;
        }
        if (screen == SCREEN_MAIN && (down & WPAD_BUTTON_HOME))
        {
            break;
        }
        if (screen == SCREEN_MAIN)
        {
            update_main(down);
        }
        else
        {
            update_music(down);
        }

        gfx_restore_background();
        if (screen == SCREEN_MAIN)
        {
            draw_main();
        }
        else
        {
            draw_music();
        }
        draw_message();
        draw_popup();
        draw_cursor();
        gfx_present();
    }

    save_settings();
    music_stop();
    WIIUPDATE_Cancel();
    WIIUPDATE_Wait(3000);
    ASND_Pause(1);
    ASND_End();
    INPUT_Shutdown();
    gfx_black();
    return 0;
}
