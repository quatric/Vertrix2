#include "music.h"

#include <asndlib.h>
#include <ctype.h>
#include <dirent.h>
#include <gccore.h>
#include <mp3player.h>
#include <ogc/lwp_watchdog.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/stat.h>

static MusicAlbum albums[MUSIC_MAX_ALBUMS];
static int album_count;

static FILE *stream;
static int current_album = -1, current_track = -1;
static int paused, shuffle, volume = 200;
/* MP3Player_IsPlaying turns true only once its thread runs: a track counts as ended only after
 * it was seen playing, or when it never starts within a second. */
static int seen_playing;
static u64 started_at;
static long data_bytes;

static volatile unsigned long decoded_samples;
static volatile unsigned sample_rate, bit_rate;
static volatile unsigned char band_levels[MUSIC_BANDS];

/* --- reading the library ------------------------------------------------------------------ */

static void utf8_to_latin1(char *text)
{
    const unsigned char *in = (const unsigned char *)text;
    char *out = text;
    while (*in)
    {
        if (in[0] < 0x80)
        {
            *out++ = (char)*in++;
        }
        else if ((in[0] & 0xe0) == 0xc0 && (in[1] & 0xc0) == 0x80)
        {
            const unsigned c = (unsigned)(in[0] & 0x1f) << 6 | (in[1] & 0x3f);
            *out++ = c < 256 ? (char)c : '?';
            in += 2;
        }
        else if (in[0] >= 0xe0 && (in[1] & 0xc0) == 0x80)
        {
            /* Beyond Latin-1: one '?' for the whole sequence. */
            *out++ = '?';
            ++in;
            while ((*in & 0xc0) == 0x80)
            {
                ++in;
            }
        }
        else
        {
            *out++ = (char)*in++; /* not UTF-8: taken as Latin-1 already */
        }
    }
    *out = 0;
}

/* An ID3v2 text frame (its encoding byte first) to Latin-1. */
static void id3_text(const unsigned char *body, unsigned size, char *out, size_t room)
{
    size_t n = 0;
    if (size == 0 || room == 0)
    {
        return;
    }
    const unsigned encoding = body[0];
    const unsigned char *p = body + 1, *end = body + size;
    if (encoding == 1 || encoding == 2)
    {
        int little = encoding == 1;
        if (encoding == 1 && end - p >= 2)
        {
            little = !(p[0] == 0xfe && p[1] == 0xff);
            if ((p[0] == 0xff && p[1] == 0xfe) || (p[0] == 0xfe && p[1] == 0xff))
            {
                p += 2;
            }
        }
        for (; end - p >= 2 && n + 1 < room; p += 2)
        {
            const unsigned c = little ? (unsigned)(p[0] | p[1] << 8) : (unsigned)(p[0] << 8 | p[1]);
            if (c == 0)
            {
                break;
            }
            out[n++] = c < 256 ? (char)c : '?';
        }
        out[n] = 0;
        return;
    }
    for (; p < end && *p && n + 1 < room; ++p)
    {
        out[n++] = (char)*p;
    }
    out[n] = 0;
    if (encoding == 3)
    {
        utf8_to_latin1(out);
    }
}

static unsigned syncsafe(const unsigned char *p)
{
    return (unsigned)(p[0] & 0x7f) << 21 | (unsigned)(p[1] & 0x7f) << 14 |
           (unsigned)(p[2] & 0x7f) << 7 | (p[3] & 0x7f);
}

/* The size of an ID3v2 tag at the start of the file (0 when none). */
static long id3_size(FILE *file)
{
    unsigned char header[10];
    fseek(file, 0, SEEK_SET);
    if (fread(header, 1, 10, file) != 10 || memcmp(header, "ID3", 3) != 0)
    {
        fseek(file, 0, SEEK_SET);
        return 0;
    }
    return 10 + (long)syncsafe(header + 6) + (header[5] & 0x10 ? 10 : 0);
}

static void read_tags(const char *path, MusicTrack *track, char *album, size_t album_room)
{
    FILE *file = fopen(path, "rb");
    if (file == NULL)
    {
        return;
    }
    unsigned char header[10];
    if (fread(header, 1, 10, file) != 10 || memcmp(header, "ID3", 3) != 0 || header[3] < 2 ||
        header[3] > 4)
    {
        fclose(file);
        return;
    }
    const unsigned version = header[3], size = syncsafe(header + 6);
    unsigned char *tag = malloc(size);
    if (tag == NULL || fread(tag, 1, size, file) != size)
    {
        free(tag);
        fclose(file);
        return;
    }
    fclose(file);
    const unsigned id_size = version == 2 ? 3 : 4, header_size = version == 2 ? 6 : 10;
    for (unsigned at = 0; at + header_size <= size;)
    {
        const unsigned char *frame = tag + at;
        if (frame[0] == 0)
        {
            break;
        }
        unsigned length;
        if (version == 2)
        {
            length = (unsigned)frame[3] << 16 | (unsigned)frame[4] << 8 | frame[5];
        }
        else if (version == 4)
        {
            length = syncsafe(frame + 4);
        }
        else
        {
            length = (unsigned)frame[4] << 24 | (unsigned)frame[5] << 16 |
                     (unsigned)frame[6] << 8 | frame[7];
        }
        if (length > size - at - header_size)
        {
            break;
        }
        const unsigned char *body = frame + header_size;
        char text[96];
        text[0] = 0;
        if (!memcmp(frame, "TIT2", id_size) || !memcmp(frame, "TT2", id_size))
        {
            id3_text(body, length, track->title, sizeof track->title);
        }
        else if (!memcmp(frame, "TPE1", id_size) || !memcmp(frame, "TP1", id_size))
        {
            id3_text(body, length, track->artist, sizeof track->artist);
        }
        else if (!memcmp(frame, "TALB", id_size) || !memcmp(frame, "TAL", id_size))
        {
            if (album[0] == 0)
            {
                id3_text(body, length, album, album_room);
            }
        }
        else if (!memcmp(frame, "TRCK", id_size) || !memcmp(frame, "TRK", id_size))
        {
            id3_text(body, length, text, sizeof text);
            track->number = atoi(text);
        }
        at += header_size + length;
    }
    free(tag);
}

static int by_track(const void *a, const void *b)
{
    const MusicTrack *x = a, *y = b;
    if (x->number != y->number)
    {
        return x->number == 0 ? 1 : (y->number == 0 ? -1 : x->number - y->number);
    }
    return strcasecmp(x->file, y->file);
}

static int by_folder(const void *a, const void *b)
{
    return strcasecmp(((const MusicAlbum *)a)->folder, ((const MusicAlbum *)b)->folder);
}

static int is_mp3(const char *name)
{
    const size_t n = strlen(name);
    return n > 4 && name[0] != '.' && strcasecmp(name + n - 4, ".mp3") == 0;
}

static void scan_album(const char *directory, const char *folder)
{
    MusicAlbum *album = &albums[album_count];
    char path[384];
    snprintf(path, sizeof path, "%s/%s", directory, folder);
    DIR *dir = opendir(path);
    if (dir == NULL)
    {
        return;
    }
    memset(album, 0, sizeof *album);
    snprintf(album->folder, sizeof album->folder, "%s", path);
    album->tracks = calloc(MUSIC_MAX_TRACKS, sizeof *album->tracks);
    if (album->tracks == NULL)
    {
        closedir(dir);
        return;
    }
    char tag_album[96] = "";
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL && album->count < MUSIC_MAX_TRACKS)
    {
        if (!is_mp3(entry->d_name))
        {
            continue;
        }
        MusicTrack *track = &album->tracks[album->count++];
        snprintf(track->file, sizeof track->file, "%s", entry->d_name);
        snprintf(path, sizeof path, "%s/%s", album->folder, entry->d_name);
        read_tags(path, track, tag_album, sizeof tag_album);
        if (track->title[0] == 0)
        {
            snprintf(track->title, sizeof track->title, "%.*s", (int)strlen(entry->d_name) - 4,
                     entry->d_name);
            utf8_to_latin1(track->title);
        }
    }
    closedir(dir);
    if (album->count == 0)
    {
        free(album->tracks);
        return;
    }
    qsort(album->tracks, (size_t)album->count, sizeof *album->tracks, by_track);
    snprintf(path, sizeof path, "%s/album.txt", album->folder);
    FILE *name = fopen(path, "rb");
    if (name != NULL)
    {
        if (fgets(album->name, sizeof album->name, name) != NULL)
        {
            album->name[strcspn(album->name, "\r\n")] = 0;
            utf8_to_latin1(album->name);
        }
        fclose(name);
    }
    if (album->name[0] == 0)
    {
        snprintf(album->name, sizeof album->name, "%s", tag_album[0] ? tag_album : folder);
        if (!tag_album[0])
        {
            utf8_to_latin1(album->name);
        }
    }
    ++album_count;
}

int music_scan(const char *directory)
{
    music_stop();
    for (int i = 0; i < album_count; ++i)
    {
        free(albums[i].tracks);
    }
    album_count = 0;
    DIR *dir = opendir(directory);
    if (dir == NULL)
    {
        return 0;
    }
    char names[MUSIC_MAX_ALBUMS][128];
    int folders = 0;
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL && folders < MUSIC_MAX_ALBUMS)
    {
        char path[384];
        struct stat info;
        snprintf(path, sizeof path, "%s/%s", directory, entry->d_name);
        if (entry->d_name[0] != '.' && stat(path, &info) == 0 && S_ISDIR(info.st_mode))
        {
            snprintf(names[folders++], sizeof names[0], "%s", entry->d_name);
        }
    }
    closedir(dir);
    for (int i = 0; i < folders; ++i)
    {
        scan_album(directory, names[i]);
    }
    qsort(albums, (size_t)album_count, sizeof *albums, by_folder);
    return album_count;
}

int music_album_count(void)
{
    return album_count;
}

const MusicAlbum *music_album(int index)
{
    return index >= 0 && index < album_count ? &albums[index] : NULL;
}

/* --- playing ------------------------------------------------------------------------------ */

static s32 read_stream(void *data, void *buffer, s32 size)
{
    return (s32)fread(buffer, 1, (size_t)size, (FILE *)data);
}

/* Called by the decoder for every frame, before synthesis: the time and the subband levels. */
static void each_frame(struct mad_stream *stream, struct mad_frame *frame)
{
    (void)stream;
    const unsigned channels = MAD_NCHANNELS(&frame->header);
    const unsigned slots = MAD_NSBSAMPLES(&frame->header);
    decoded_samples += 32 * slots;
    sample_rate = frame->header.samplerate;
    if (bit_rate == 0)
    {
        bit_rate = (unsigned)frame->header.bitrate;
    }
    for (unsigned band = 0; band < MUSIC_BANDS; ++band)
    {
        mad_fixed_t peak = 0;
        for (unsigned c = 0; c < channels; ++c)
        {
            for (unsigned s = 0; s < slots; ++s)
            {
                mad_fixed_t v = frame->sbsample[c][s][band];
                v = v < 0 ? -v : v;
                peak = v > peak ? v : peak;
            }
        }
        /* MAD_F_ONE (1 << 28) is full scale: 18 steps an octave over the top 14 octaves, the
         * high bands (quieter in music) lifted a little. */
        const int octave = peak > 0 ? 31 - __builtin_clz((unsigned)peak) : 0;
        int level = (octave - 14) * 18 + (int)band * 3;
        level = level < 0 ? 0 : level;
        band_levels[band] = (unsigned char)(level > 255 ? 255 : level);
    }
}

static void close_stream(void)
{
    MP3Player_Stop();
    if (stream != NULL)
    {
        fclose(stream);
        stream = NULL;
    }
}

void music_stop(void)
{
    close_stream();
    if (paused)
    {
        ASND_Pause(0);
        paused = 0;
    }
    current_album = current_track = -1;
    memset((void *)band_levels, 0, sizeof band_levels);
}

void music_play(int album, int track)
{
    const MusicAlbum *a = music_album(album);
    close_stream();
    if (paused)
    {
        ASND_Pause(0);
        paused = 0;
    }
    if (a == NULL || track < 0 || track >= a->count)
    {
        current_album = current_track = -1;
        return;
    }
    char path[384];
    snprintf(path, sizeof path, "%s/%s", a->folder, a->tracks[track].file);
    current_album = album;
    current_track = track;
    decoded_samples = 0;
    sample_rate = bit_rate = 0;
    seen_playing = 0;
    started_at = gettime();
    stream = fopen(path, "rb");
    if (stream == NULL)
    {
        return; /* music_update moves on */
    }
    fseek(stream, 0, SEEK_END);
    const long size = ftell(stream);
    const long skip = id3_size(stream);
    data_bytes = size - skip;
    fseek(stream, skip, SEEK_SET);
    MP3Player_Volume((u32)volume);
    MP3Player_PlayFile(stream, read_stream, each_frame);
}

static int random_below(int n)
{
    return n > 0 ? (int)((gettime() >> 3) % (u64)n) : 0;
}

void music_next(void)
{
    const MusicAlbum *a = music_album(current_album);
    if (a == NULL)
    {
        return;
    }
    int next = current_track + 1;
    if (shuffle && a->count > 1)
    {
        next = random_below(a->count - 1);
        next += next >= current_track;
    }
    music_play(current_album, next % a->count);
}

void music_previous(void)
{
    const MusicAlbum *a = music_album(current_album);
    if (a == NULL)
    {
        return;
    }
    if (music_elapsed() > 3)
    {
        music_play(current_album, current_track); /* from the start, as players do */
        return;
    }
    music_play(current_album, (current_track + a->count - 1) % a->count);
}

void music_toggle_pause(void)
{
    if (current_track < 0)
    {
        return;
    }
    paused = !paused;
    ASND_Pause(paused);
}

void music_update(void)
{
    if (current_track < 0 || paused)
    {
        return;
    }
    if (MP3Player_IsPlaying())
    {
        seen_playing = 1;
        return;
    }
    if (seen_playing || ticks_to_millisecs(gettime() - started_at) > 1000)
    {
        music_next();
    }
}

int music_playing(void)
{
    return current_track >= 0;
}

int music_paused(void)
{
    return paused;
}

int music_current_album(void)
{
    return current_album;
}

int music_current_track(void)
{
    return current_track;
}

void music_set_shuffle(int on)
{
    shuffle = on;
}

int music_shuffle(void)
{
    return shuffle;
}

void music_set_volume(int value)
{
    volume = value < 0 ? 0 : (value > 255 ? 255 : value);
    MP3Player_Volume((u32)volume);
}

int music_volume(void)
{
    return volume;
}

int music_elapsed(void)
{
    return sample_rate ? (int)(decoded_samples / sample_rate) : 0;
}

int music_length(void)
{
    return bit_rate ? (int)(data_bytes * 8 / (long)bit_rate) : 0;
}

void music_levels(unsigned char *levels)
{
    memcpy(levels, (const void *)band_levels, MUSIC_BANDS);
}
