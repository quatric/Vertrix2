#ifndef VERTRIX_MAC_DATA_H
#define VERTRIX_MAC_DATA_H

/* The games' own files on the Mac. Each game reads and writes a folder of its own in the Vertrix
 * folder ($VERTRIX_HOME, else ~/Library/Application Support/Vertrix): its archive or release, its
 * settings, its scores and its log. The app comes without them; a build may carry copies in
 * Vertrix.app/Contents/Resources/Data/<folder>/, which are copied out on first use. */

#include "vertrix_games.h"

/* The Vertrix folder, created. */
const char *vertrix_home(void);
/* A game's folder, <home>/<folder>, created. */
const char *vertrix_game_folder(const VertrixGame *game);
/* Whether `folder` holds the file the game needs (any case). */
int vertrix_game_ready(const VertrixGame *game, const char *folder);
/* Copies the build's own copy of the game's files into `folder`; nonzero when it is then ready. */
int vertrix_import_bundled(const VertrixGame *game, const char *folder);
/* Main thread: asks for the game's files (an open panel) and copies them into `folder`; nonzero
 * when it is then ready, 0 when the player cancelled. */
int vertrix_import_ask(const VertrixGame *game, const char *folder);

#endif
