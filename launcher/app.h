#ifndef VERTRIX_APP_H
#define VERTRIX_APP_H

/* One Homebrew Channel app for every game (launcher/README.md). The launcher in
 * sd:/apps/vertrix/boot.dol starts a game's DOL from sd:/apps/vertrix/games/ with
 *
 *     argv[0] = the game's DOL, argv[1] = its data folder, argv[2] = the launcher's DOL,
 *
 * and each game goes back to argv[2] when it ends. Started on its own (no arguments), a game
 * keeps its old folder and returns to the loader as before. */

/* Keep main's arguments for the calls below. */
void vertrix_app_init(int argc, char **argv);

/* The data folder: argv[1] when the launcher started the game, else standalone. */
const char *vertrix_app_directory(const char *standalone);

/* Nonzero when the launcher started the game. */
int vertrix_app_from_launcher(void);

/* Memory the boot may load the next DOL into, for a game whose own heap fills MEM2 (the default
 * is the top of MEM2's arena). The region must be unused by then. */
void vertrix_app_set_scratch(void *start, unsigned size);

/* Boots the DOL at path (plain or packed by dolxz) with argc arguments, args[0] being the path.
 * Shuts the system down first, so call it only once the app has stopped its own threads, voices
 * and controllers. Returns only when the file cannot be read or is not a DOL. */
int vertrix_app_boot(const char *path, int argc, const char *const *args);

/* Back to the launcher when it started the game; returns otherwise (or when that fails). */
void vertrix_app_return(void);

#endif
