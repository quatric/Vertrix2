#ifndef VERTRIX_MAC_VERTRIX_GAMES_H
#define VERTRIX_MAC_VERTRIX_GAMES_H

/* The four games of the Mac app, as the Wii launcher lists them (launcher/main.c). */

typedef struct
{
    const char *title;
    const char *year;
    const char *about;
    const char *folder; /* its files, in the Vertrix folder; also its app's name in Helpers/ */
    const char *needs;  /* a file that must be in the folder */
    const char *needs_text;
    int whole_release; /* the game reads every file of its release, not one archive */
} VertrixGame;

enum
{
    VERTRIX_GAMES = 4
};

extern const VertrixGame vertrix_games[VERTRIX_GAMES];

/* The game whose folder is `folder`, or NULL. */
const VertrixGame *vertrix_game(const char *folder);

#endif
