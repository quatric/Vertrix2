#include "games.h"

static const VertrixGame GAMES[VERTRIX_GAME_COUNT] = {
    {VERTRIX_GAME_2, "Vertrix 2", "sd:/apps/vertrix2", "Vertrix2.vf",
     "4db546b7957136179bedf22a37b7e5db401ea25bc668b715643adf84ce525e28"},
    {VERTRIX_GAME_3, "Vertrix 3", "sd:/apps/vertrix3", "vertrix3.vf",
     "db625cfe1acb3f5f70d30d041362831ca59ec72b5693e463331cf2f29738f7e9"},
};

const VertrixGame *vertrix_game(VertrixGameId id)
{
    return (unsigned)id < VERTRIX_GAME_COUNT ? &GAMES[id] : NULL;
}

const VertrixGame *vertrix_game_of_archive(const VertrixVf *archive)
{
    uint32_t index;
    const int three = vertrix_vf_find(archive, ".\\texte\\MeshesFileName.ini", &index);
    const int two = vertrix_vf_find(archive, ".\\texte\\SpriteFileName.ini", &index);
    if (three == two)
    {
        return NULL;
    }
    return vertrix_game(three ? VERTRIX_GAME_3 : VERTRIX_GAME_2);
}
