#ifndef VERTRIX_LAUNCHER_COMPAT_H
#define VERTRIX_LAUNCHER_COMPAT_H

/* The Wii launcher (launcher/main.c, music.c) built for a console: the few calls it makes of
 * libogc, libwiiinput and libwiiupdate, under the same names, on the console shell
 * (consoles/launcher_shell.c). The headers next to this one (gccore.h, asndlib.h, ...) only
 * include it. The controllers' buttons arrive as the Wii Remote's:
 *
 *   A (right face button)   A        choose, play
 *   B (bottom)              B        back
 *   X (top)                 1        shuffle
 *   Y (left)                2        pause
 *   L, R                    Minus, Plus   previous and next track
 *   Plus (START on the 3DS) HOME     leave the launcher
 *
 * and the touch screen is the Wii Remote's pointer: a tap is A where it touched. */

#include <mad.h>
#include <stdbool.h>
#include <stdint.h>

typedef int32_t s32;
typedef uint32_t u32;
typedef uint64_t u64;
typedef uint8_t u8;
#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

/* launcher/main.c's main runs on the shell's thread, started by launcher_shell.c's main. */
#ifndef VERTRIX_LAUNCHER_SHELL
#define main launcher_main
#endif

/* --- what differs from the Wii in the launcher's text and files ---------------------------- */

#include "console.h"

#define LAUNCHER_HOME console_app_folder()
#define LAUNCHER_PROGRAM_EXTENSION console_program_extension
#define LAUNCHER_PROGRAM_STATE(path) console_program_state(path)
#if defined(__3DS__)
#define LAUNCHER_HINT_EXIT "START: Exit"
#else
#define LAUNCHER_HINT_EXIT "+: Exit"
#endif
#define LAUNCHER_HINT_MUSIC "A: Play  Y: Pause  L/R: Prev/Next  X: Shuffle  B: Back"

/* --- libogc -------------------------------------------------------------------------------- */

/* Microseconds; ticks_to_millisecs turns them into milliseconds. */
u64 gettime(void);
#define ticks_to_millisecs(ticks) ((ticks) / 1000u)

#define VIDEO_SetBlack(black) ((void)(black))
#define SYS_STDIO_Report(on) ((void)(on))

/* The card is the system's own, mounted before the launcher starts. */
#define fatInitDefault() 1

void ASND_Init(void);
void ASND_End(void);
void ASND_Pause(s32 paused);

/* libogc's MP3 player on libmad: a thread decodes the file into the shell's sound stream. */
void MP3Player_Init(void);
s32 MP3Player_PlayFile(void *cb_data, s32 (*reader)(void *, void *, s32),
                       void (*filterfunc)(struct mad_stream *, struct mad_frame *));
void MP3Player_Stop(void);
bool MP3Player_IsPlaying(void);
void MP3Player_Volume(u32 volume);

/* --- libwiiinput --------------------------------------------------------------------------- */

enum
{
    WPAD_BUTTON_2 = 0x0001,
    WPAD_BUTTON_1 = 0x0002,
    WPAD_BUTTON_B = 0x0004,
    WPAD_BUTTON_A = 0x0008,
    WPAD_BUTTON_MINUS = 0x0010,
    WPAD_BUTTON_HOME = 0x0080,
    WPAD_BUTTON_LEFT = 0x0100,
    WPAD_BUTTON_RIGHT = 0x0200,
    WPAD_BUTTON_DOWN = 0x0400,
    WPAD_BUTTON_UP = 0x0800,
    WPAD_BUTTON_PLUS = 0x1000
};
#define INPUT_STICK_LEFT 0

s32 INPUT_Init(void);
void INPUT_Shutdown(void);
void INPUT_SetScreenSize(int width, int height);
void INPUT_Update(void);
u32 INPUT_ButtonsHeld(void);
u32 INPUT_ButtonsDown(void);
/* The stick is part of the D-pad's buttons already: always centred. */
float INPUT_Stick(int which, float *x, float *y, const char **source);
bool INPUT_CursorActive(void);
void INPUT_CursorPosition(int *x, int *y);
bool INPUT_CursorMoved(void);
void INPUT_MouseDelta(int *dx, int *dy, int *wheel);

/* --- libwiiupdate: updates come from the release page, not from the app -------------------- */

enum
{
    WIIUPDATE_POPUP_CLOSED = 0,
    WIIUPDATE_POPUP_OPEN,
    WIIUPDATE_POPUP_EXIT
};
typedef struct
{
    const char *title;
    char text[160];
    const char *detail;
    const char *hint;
    int progress;
} wiiupdate_popup;
static inline void WIIUPDATE_SetAppPath(const char *path)
{
    (void)path;
}

static inline int WIIUPDATE_Start(const char *owner, const char *repo, const char *version)
{
    (void)owner;
    (void)repo;
    (void)version;
    return 0;
}

static inline void WIIUPDATE_Cancel(void)
{
}

static inline int WIIUPDATE_Wait(int timeout_ms)
{
    (void)timeout_ms;
    return 0;
}

static inline int WIIUPDATE_Popup(u32 down, wiiupdate_popup *popup)
{
    (void)down;
    (void)popup;
    return WIIUPDATE_POPUP_CLOSED;
}

#endif
