#include "wii_archive.h"
#include <fat.h>
#include <sdcard/wiisd_io.h>

VertrixWiiArchiveResult vertrix_wii_archive_open(VertrixWiiArchive *storage)
{
    if (!storage || storage->archive || storage->mounted)
    {
        return VERTRIX_WII_ARCHIVE_INVALID_STATE;
    }
    if (!fatMountSimple("sd", &__io_wiisd))
    {
        return VERTRIX_WII_ARCHIVE_MOUNT_FAILED;
    }
    storage->mounted = 1;
    storage->archive = vertrix_vf_open(VERTRIX_WII_VF_PATH);
    if (!storage->archive)
    {
        vertrix_wii_archive_close(storage);
        return VERTRIX_WII_ARCHIVE_OPEN_FAILED;
    }
    return VERTRIX_WII_ARCHIVE_OK;
}

void vertrix_wii_archive_close(VertrixWiiArchive *storage)
{
    if (!storage)
    {
        return;
    }
    vertrix_vf_close(storage->archive);
    storage->archive = NULL;
    if (storage->mounted)
    {
        fatUnmount("sd");
        storage->mounted = 0;
    }
}
