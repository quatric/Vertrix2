#include "wii_archive.h"
#include <fat.h>
#include <sdcard/wiisd_io.h>
#include <stdio.h>

VertrixWiiArchiveResult vertrix_wii_archive_open(VertrixWiiArchive *storage)
{
    return vertrix_wii_archive_open_game(storage, vertrix_game(VERTRIX_GAME_2));
}

VertrixWiiArchiveResult vertrix_wii_archive_open_game(VertrixWiiArchive *storage,
                                                      const VertrixGame *game)
{
    char path[128];
    if (!storage || storage->archive || storage->mounted || !game ||
        snprintf(path, sizeof path, "%s/%s", game->directory, game->archive) >= (int)sizeof path)
    {
        return VERTRIX_WII_ARCHIVE_INVALID_STATE;
    }
    if (!fatMountSimple("sd", &__io_wiisd))
    {
        return VERTRIX_WII_ARCHIVE_MOUNT_FAILED;
    }
    storage->mounted = 1;
    storage->archive = vertrix_vf_open(path);
    if (!storage->archive || vertrix_game_of_archive(storage->archive) != game)
    {
        vertrix_wii_archive_close(storage);
        return VERTRIX_WII_ARCHIVE_OPEN_FAILED;
    }
    storage->game = game;
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
    storage->game = NULL;
    if (storage->mounted)
    {
        fatUnmount("sd");
        storage->mounted = 0;
    }
}
