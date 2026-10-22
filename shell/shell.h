#ifndef VERTRIX_SHELL_H
#define VERTRIX_SHELL_H

/* What a recompiled game needs of the system it runs on: a screen that shows its frames, the
 * keyboard, the mouse and game controllers, a sound stream, and the folder that holds the game's
 * own files. The drivers (vertrix3/shell/shell_main.c, vertrix1/shell/shell_main.c) turn these
 * into the machine each game expects. mac/shell.m is the Mac's (mac/README.md);
 * consoles/shell_sdl.c (Switch, Wii U) and consoles/shell_3ds.c are the consoles'
 * (consoles/README.md). */

#include <stddef.h>
#include <stdint.h>

#include "vertrix_games.h"

typedef struct
{
    const VertrixGame *game;
    /* The picture's size before the first frame, and the shape it is shown at (0: the frame's
     * own; Vertrix's VGA modes fill a 4:3 screen). */
    unsigned width, height;
    double aspect;
    /* The game draws its own cursor: hide the Mac's over the picture. */
    int hide_cursor;
} ShellOptions;

/* The system's name, for the log ("the Mac", "the Switch"). */
extern const char shell_platform[];

/* On the main thread, first: the app, its window, and the game's folder. On the Mac the folder
 * gets the game's files when it lacks them (from the app or from the player, mac/data.h), and
 * --data DIR names it; on a console it is the one the launcher passes, else the game's folder in
 * the app's. Returns the folder. */
const char *shell_start(int argc, char **argv, const ShellOptions *options);

/* A file of the app's Resources (on a console, one built into the program) read whole
 * (malloc'd), or NULL. */
uint8_t *shell_resource(const char *name, size_t *size);

/* Runs `game` on its own thread (a large stack) and the app on this one. */
_Noreturn void shell_run(void (*game)(void));

/* The log: <folder>/<name>, and stderr. */
void shell_log_open(const char *name);
void shell_log(const char *line);

/* An error the game cannot go on from: shown, then the app ends. */
_Noreturn void shell_fatal(const char *message);

/* The game has ended (any thread): the app ends with `code`, and on a console the launcher
 * starts again. */
_Noreturn void shell_exit(int code);

uint64_t shell_microseconds(void);

/* --- video --------------------------------------------------------------------------------- */

/* A finished picture, 0xAARRGGBB rows, from any thread (copied). */
void shell_present(const uint32_t *pixels, unsigned width, unsigned height);
/* Called on the main thread before each refresh of the screen (a driver that reads the picture
 * from its machine presents it there). */
void shell_set_refresh(void (*refresh)(void));
/* Waits for the next 60 Hz frame, as a Flip waits for the vertical blank. */
void shell_wait_frame(void);

/* --- input --------------------------------------------------------------------------------- */

enum
{
    SHELL_KEY,   /* code: a set 1 scan code, 0x100 for the E0 prefix */
    SHELL_BUTTON /* code: 0 left, 1 right, 2 middle */
};

typedef struct
{
    int kind;
    unsigned code;
    int down;
    int repeat; /* a key held down, typed again */
} ShellInput;

/* The next input since the last call (any thread); 0 when there is none. */
int shell_input(ShellInput *input);
/* Where the pointer (on a console, the touch screen) is, in the last frame's pixels, clamped to
 * it; 0 when it is outside the picture or nothing touches the screen. */
int shell_pointer(int *x, int *y);

/* Game controllers, the first two connected. */
enum
{
    SHELL_PAD_UP = 1u << 0,
    SHELL_PAD_DOWN = 1u << 1,
    SHELL_PAD_LEFT = 1u << 2,
    SHELL_PAD_RIGHT = 1u << 3,
    SHELL_PAD_A = 1u << 4, /* the bottom face button */
    SHELL_PAD_B = 1u << 5, /* the right one */
    SHELL_PAD_X = 1u << 6, /* the left one */
    SHELL_PAD_Y = 1u << 7, /* the top one */
    SHELL_PAD_MENU = 1u << 8,
    SHELL_PAD_OPTIONS = 1u << 9,
    SHELL_PAD_SHOULDER_L = 1u << 10,
    SHELL_PAD_SHOULDER_R = 1u << 11
};
uint32_t shell_pad(unsigned player);

/* The player closed the window or quit the app (on a console, the system asked the app to close,
 * or Minus and Plus were pressed together): the driver asks the game to end. */
int shell_quit_requested(void);

/* --- sound --------------------------------------------------------------------------------- */

/* PCM: 8-bit samples are unsigned, 16-bit signed; channels interleaved. Opening again with a
 * new format drops what was queued. */
void shell_audio_open(uint32_t rate, uint32_t channels, uint32_t bits);
/* Queues samples; waits while the queue is full. */
void shell_audio_write(const uint8_t *samples, uint32_t bytes);
/* Bytes played since the stream opened, and bytes queued but not yet played. */
uint64_t shell_audio_played(void);
uint32_t shell_audio_queued(void);

#endif
