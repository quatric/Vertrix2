#ifndef VERTRIX_LAUNCHER_MUSIC_H
#define VERTRIX_LAUNCHER_MUSIC_H

/* The soundtrack player. Albums are the folders in <app>/music/, each holding MP3 files; an
 * optional album.txt names the album (its first line), else the tracks' ID3 album tag or the
 * folder's name is used. Tracks are ordered by their ID3 track number, then by file name. */

enum
{
    MUSIC_MAX_ALBUMS = 16,
    MUSIC_MAX_TRACKS = 128,
    MUSIC_BANDS = 32
};

typedef struct
{
    char file[128];
    char title[96];
    char artist[64];
    int number;
} MusicTrack;

typedef struct
{
    char folder[128];
    char name[96];
    int count;
    MusicTrack *tracks;
} MusicAlbum;

/* Reads the albums in directory (e.g. "sd:/apps/vertrix/music"); returns how many. */
int music_scan(const char *directory);
int music_album_count(void);
const MusicAlbum *music_album(int index);

/* Starts a track; the player then goes on to the next one in the album (and round again). */
void music_play(int album, int track);
/* Starts a random track of any album. */
void music_play_random(void);
void music_stop(void);
void music_toggle_pause(void);
void music_next(void);
void music_previous(void);
/* Once a frame: starts the next track when one ends. */
void music_update(void);

int music_playing(void); /* a track is loaded, paused or not */
int music_paused(void);
int music_current_album(void);
int music_current_track(void);
void music_set_shuffle(int on);
int music_shuffle(void);
/* 0..255 */
void music_set_volume(int volume);
int music_volume(void);

/* Seconds played and the track's estimated length (0 when unknown). */
int music_elapsed(void);
int music_length(void);
/* MUSIC_BANDS levels 0..255 from the decoder's subband samples, for the visualiser. */
void music_levels(unsigned char *levels);

#endif
