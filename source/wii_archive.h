#ifndef VERTRIX_WII_ARCHIVE_H
#define VERTRIX_WII_ARCHIVE_H
#include "games.h"
#include "vf.h"

#define VERTRIX_WII_VF_PATH "sd:/apps/vertrix2/Vertrix2.vf"

typedef struct
{
    VertrixVf *archive;
    unsigned mounted;
    /* The game whose archive is open. */
    const VertrixGame *game;
} VertrixWiiArchive;

typedef enum
{
    VERTRIX_WII_ARCHIVE_OK = 0,
    VERTRIX_WII_ARCHIVE_INVALID_STATE,
    VERTRIX_WII_ARCHIVE_MOUNT_FAILED,
    VERTRIX_WII_ARCHIVE_OPEN_FAILED
} VertrixWiiArchiveResult;

/* Startup owns the sd mount exclusively. Initialize storage to zero.
 * Reads the original archive in place; failure releases an acquired mount.
 * Keep storage alive until all asset reads finish. No concurrent access. */
VertrixWiiArchiveResult vertrix_wii_archive_open(VertrixWiiArchive *storage);
/* The same for a given game: its archive at <directory>/<archive> on SD. The archive must be
 * that game's (vertrix_game_of_archive), else the open fails. */
VertrixWiiArchiveResult vertrix_wii_archive_open_game(VertrixWiiArchive *storage,
                                                      const VertrixGame *game);
/* Close archive before releasing its SD mount. Safe on zeroed storage. */
void vertrix_wii_archive_close(VertrixWiiArchive *storage);
#endif
