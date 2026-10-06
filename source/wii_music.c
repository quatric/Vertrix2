#include "wii_music.h"
#include <asndlib.h>
#include <gccore.h>
#include <limits.h>
#include <stdlib.h>

struct VertrixWiiMusic
{
    VertrixSequencePlayer *player;
    int32_t *scratch;
    void *allocations[3];
    uint8_t *buffers[3];
    size_t frames;
    uint32_t rate;
    int bytes;
    int voice;
    int pending;
    unsigned started;
    unsigned playing;
    unsigned failed;
};

/* Keep a starved ASND voice waiting. Rendering stays in the main loop. */
static void music_wait(s32 voice)
{
    (void)voice;
}

void vertrix_wii_music_free(VertrixWiiMusic *music)
{
    if (!music)
    {
        return;
    }
    if (music->playing)
    {
        ASND_StopVoice(music->voice);
    }
    vertrix_sequence_player_free(music->player);
    free(music->scratch);
    for (unsigned index = 0; index < 3; index++)
    {
        free(music->allocations[index]);
    }
    free(music);
}

VertrixWiiMusic *vertrix_wii_music_create(const VertrixSequenceModule *module, uint32_t rate,
                                          uint32_t master_gain, int interpolate, size_t frames)
{
    if (!module || !rate || rate > MAX_PITCH || !frames || frames % 8 ||
        frames > (INT_MAX - 31) / 4 || frames > SIZE_MAX / 2 / sizeof(int32_t))
    {
        return NULL;
    }
    VertrixWiiMusic *music = calloc(1, sizeof(*music));
    if (!music)
    {
        return NULL;
    }
    music->pending = -1;
    music->frames = frames;
    music->rate = rate;
    music->bytes = (int)(frames * 4);
    music->player = vertrix_sequence_player_create(module, rate, master_gain, 1, interpolate);
    music->scratch = malloc(frames * 2 * sizeof(*music->scratch));
    for (unsigned index = 0; index < 3; index++)
    {
        music->allocations[index] = malloc((size_t)music->bytes + 31);
        if (music->allocations[index])
        {
            music->buffers[index] =
                (uint8_t *)(((uintptr_t)music->allocations[index] + 31) & ~(uintptr_t)31);
        }
    }
    if (!music->player || !music->scratch || !music->buffers[0] || !music->buffers[1] ||
        !music->buffers[2])
    {
        vertrix_wii_music_free(music);
        return NULL;
    }
    return music;
}

static int music_render(VertrixWiiMusic *music, unsigned index)
{
    if (!vertrix_sequence_player_pcm(music->player, music->frames, 1, music->scratch,
                                     music->frames * 2, music->buffers[index],
                                     (size_t)music->bytes))
    {
        music->failed = 1;
        return 0;
    }
    DCFlushRange(music->buffers[index], (uint32_t)music->bytes);
    return 1;
}

int vertrix_wii_music_start(VertrixWiiMusic *music, int voice, unsigned left, unsigned right)
{
    if (!music || music->started || music->failed || voice < 0 || voice >= MAX_SND_VOICES ||
        left > MAX_VOLUME || right > MAX_VOLUME)
    {
        return 0;
    }
    music->started = 1;
    if (!music_render(music, 0) || !music_render(music, 1))
    {
        return 0;
    }
    if (ASND_SetVoice(voice, VOICE_STEREO_16BIT_LE, (int)music->rate, 0, music->buffers[0],
                      music->bytes, (int)left, (int)right, music_wait) != SND_OK)
    {
        music->failed = 1;
        return 0;
    }
    music->voice = voice;
    music->playing = 1;
    music->pending = 1;
    return vertrix_wii_music_pump(music) >= 0;
}

int vertrix_wii_music_pump(VertrixWiiMusic *music)
{
    if (!music || !music->playing || music->failed)
    {
        return -1;
    }
    int ready = ASND_TestVoiceBufferReady(music->voice);
    if (ready < 0)
    {
        music->failed = 1;
        return -1;
    }
    if (!ready)
    {
        return 0;
    }
    if (music->pending < 0)
    {
        for (unsigned index = 0; index < 3; index++)
        {
            int used = ASND_TestPointer(music->voice, music->buffers[index]);
            if (used < 0)
            {
                music->failed = 1;
                return -1;
            }
            if (!used)
            {
                if (!music_render(music, index))
                {
                    return -1;
                }
                music->pending = (int)index;
                break;
            }
        }
    }
    if (music->pending < 0)
    {
        return 0;
    }
    int result = ASND_AddVoice(music->voice, music->buffers[music->pending], music->bytes);
    if (result == SND_BUSY)
    {
        return 0;
    }
    if (result != SND_OK)
    {
        music->failed = 1;
        return -1;
    }
    music->pending = -1;
    return 1;
}
