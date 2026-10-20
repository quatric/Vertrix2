#ifndef VERTRIX_GAMES_H
#define VERTRIX_GAMES_H

#include "vf.h"

/* The games this port reads. Both ship one VF v10 archive beside the executable; the archive
 * reader, the XM/MP3/WAV/PCX/TAB loaders and the music are shared (docs/VERTRIX3.md). */
typedef enum
{
    VERTRIX_GAME_2 = 0,
    VERTRIX_GAME_3,
    VERTRIX_GAME_COUNT
} VertrixGameId;

typedef struct
{
    VertrixGameId id;
    const char *title;
    /* The SD card directory (Homebrew Channel layout) and the archive's original file name. */
    const char *directory;
    const char *archive;
    /* SHA-256 of the original Windows executable the recovered code is checked against. */
    const char *executable_sha256;
} VertrixGame;

const VertrixGame *vertrix_game(VertrixGameId id);
/* Which game an open archive belongs to: Vertrix 3's alone lists .\texte\MeshesFileName.ini
 * (its Direct3D meshes) and Vertrix 2's alone lists .\texte\SpriteFileName.ini. NULL for
 * neither or both. */
const VertrixGame *vertrix_game_of_archive(const VertrixVf *archive);

#endif
