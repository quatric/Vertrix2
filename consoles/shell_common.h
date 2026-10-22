#ifndef VERTRIX_SHELL_COMMON_H
#define VERTRIX_SHELL_COMMON_H

/* The part of shell/shell.h that is the same on every console (shell_common.c), under the part
 * that shows the picture and plays the sound (shell_sdl.c on the Switch and the Wii U,
 * shell_3ds.c). */

#include <stdint.h>

#include "shell.h"

extern ShellOptions common_options;

/* The game's folder (shell_start); the app's own folder for the launcher. */
const char *common_start(int argc, char **argv, const ShellOptions *options);

/* --- the main thread's frame --------------------------------------------------------------- */

/* Calls the driver's refresh hook, then hands the latest picture to `show` (under the frame's
 * lock; `fresh` when it changed since the last call). */
void common_show(void (*show)(const uint32_t *pixels, unsigned width, unsigned height, int fresh));

/* The controllers and touch screen into shell_pad, shell_pointer and the input queue; the touch
 * screen's point already in the picture's pixels (inside 0 when off the picture). Minus and Plus
 * held together ask the game to end. */
void common_input(const uint32_t pads[2], int touched, int inside, int x, int y);

/* A key of a keyboard: its set 1 scan code (0x100: the E0 prefix). */
void common_key(unsigned scan_code, int down);

/* The system asked the app to close: the game is asked to end, and the launcher does not start
 * again after it. */
void common_request_quit(void);

/* The launcher's start of a game: console_chain, remembered so that the program's end does not
 * start the launcher again. */
int common_chain(const char *path, const char *argument);

/* Starts the game's thread (shell_run; a NULL game only shows the error). */
void common_start_game(void (*game)(void));

/* The game has ended or stopped on an error; the main loop then finishes. */
int common_finished(void);
/* An error to show (shell_fatal), or NULL. */
const char *common_error(void);
/* The canvas with the error, for the screen (launcher/gfx.c's canvas, GFX_WIDTH x GFX_HEIGHT). */
const uint32_t *common_error_canvas(void);

/* The program's end, on the main thread: the launcher again after a game (unless the system
 * asked the app to close), or what the launcher chose. */
void common_finish(void);

/* --- sound --------------------------------------------------------------------------------- */

/* Fills `frames` stereo frames at `rate` from the queued stream (silence when there is none or
 * it is paused); any thread. */
void common_audio_mix(int16_t *out, unsigned frames, unsigned rate);
/* Paused, the stream keeps what is queued and plays nothing (the launcher's music). */
void common_audio_pause(int paused);

#endif
