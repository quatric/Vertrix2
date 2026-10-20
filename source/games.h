#ifndef VERTRIX_GAMES_H
#define VERTRIX_GAMES_H

#include "vf.h"

/* The games this port reads. Each ships one VF v10 archive beside the executable; the archive
 * reader, the XM/MP3/WAV/PCX/TAB loaders and the music are shared (docs/VERTRIX3.md). Vertrix 2
 * v2.0 (2003) is the version the recovered code comes from; v1.2 (2001) is the earlier release
 * (docs/VERTRIX2-V12.md). */
typedef enum
{
    VERTRIX_GAME_2 = 0,
    VERTRIX_GAME_3,
    VERTRIX_GAME_2_V12,
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
 * (its Direct3D meshes) and Vertrix 2's alone lists .\texte\SpriteFileName.ini; of the two
 * Vertrix 2 releases only v2.0 lists .\texte\BombesFileName.ini (the bombs it added). NULL for
 * neither or both. */
const VertrixGame *vertrix_game_of_archive(const VertrixVf *archive);

#endif
