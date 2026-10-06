#ifndef VERTRIX_WII_ARCHIVE_H
#define VERTRIX_WII_ARCHIVE_H
#include "vf.h"

#define VERTRIX_WII_VF_PATH "sd:/apps/vertrix2/Vertrix2.vf"

typedef struct
{
    VertrixVf *archive;
    unsigned mounted;
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
/* Close archive before releasing its SD mount. Safe on zeroed storage. */
void vertrix_wii_archive_close(VertrixWiiArchive *storage);
#endif
