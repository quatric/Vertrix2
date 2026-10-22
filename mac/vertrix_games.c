#include "vertrix_games.h"

#include <string.h>

const VertrixGame vertrix_games[VERTRIX_GAMES] = {
    {"Vertrix", "1997", "The original, for DOS", "vertrix1", "BIN1.BIN",
     "the whole original release (VERTRIX.EXE, BIN1.BIN, BIN2.BIN and the rest)", 1},
    {"Vertrix 2 v1.2", "2001", "The first Windows release", "vertrix2-v12", "Vertrix2.vf",
     "Vertrix2.vf from Vertrix 2 v1.2", 0},
    {"Vertrix 2", "2003", "Version 2.0", "vertrix2", "Vertrix2.vf",
     "Vertrix2.vf from Vertrix 2 v2.0", 0},
    {"Vertrix 3", "2009", "In 3D", "vertrix3", "VERTRIX3.VF", "VERTRIX3.VF from Vertrix 3", 0},
};

const VertrixGame *vertrix_game(const char *folder)
{
    for (int i = 0; i < VERTRIX_GAMES; ++i)
    {
        if (strcmp(vertrix_games[i].folder, folder) == 0)
        {
            return &vertrix_games[i];
        }
    }
    return 0;
}
