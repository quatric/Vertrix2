#ifndef VERTRIX_CONSOLE_H
#define VERTRIX_CONSOLE_H

/* What differs between the consoles under the shell (consoles/README.md): where the app lives,
 * the clock, the controllers, and how one program starts another. system_switch.c,
 * system_wiiu.c and system_3ds.c implement it.
 *
 *   Switch   sdmc:/switch/vertrix/vertrix.nro              the launcher
 *            sdmc:/switch/vertrix/games/<folder>.nro       the games
 *   Wii U    sd:/wiiu/apps/vertrix/vertrix.wuhb            the launcher
 *            sd:/wiiu/apps/vertrix/games/<folder>.rpx      the games
 *   3DS      sdmc:/3ds/vertrix/vertrix.3dsx                the launcher
 *            sdmc:/3ds/vertrix/games/<folder>.3dsx         the games
 *
 * and each game's files in <app folder>/<folder>/, the music in <app folder>/music/<album>/. */

#include <stdint.h>

/* The system's name is shell_platform (shell/shell.h), "the Switch". */

/* ".nro" */
extern const char console_program_extension[];

/* Once, first: the system's services the app needs (the SD card, the controllers). */
void console_init(void);

/* The app's folder, without a trailing slash. */
const char *console_app_folder(void);
/* The launcher's program. */
const char *console_launcher_path(void);

uint64_t console_microseconds(void);

/* The controllers: the first two players' SHELL_PAD_* buttons (the stick counts as the D-pad;
 * SHELL_PAD_A is the bottom face button, B the right one), and the touch screen in the
 * screen's own coordinates (touched 0 when nothing touches it). Main thread, once a frame. */
void console_read_input(uint32_t pads[2], int *touched, int *touch_x, int *touch_y);

/* After this program ends, the system starts `path` with `argument` (NULL for none). Nonzero
 * when it can (from the homebrew loader; not in an emulator that loaded the program alone). */
int console_chain(const char *path, const char *argument);

/* The program's last step, on the main thread: starts what console_chain set, or goes back to
 * the system's menu (closing: the system already asked the app to close). Returns when the
 * program may end. */
void console_finish(int closing);

#endif
