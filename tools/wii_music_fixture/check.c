#include "asndlib.h"
#include "wii_music.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
static void *active, *queued;
static VertrixSequencePlayer *reference;
static unsigned submitted, flushed, busy, invalid, stopped;
static void (*handler)(s32);
static void compare(void *data, int bytes)
{
    int32_t scratch[128];
    unsigned char expected[256];
    assert(bytes == 256 && ((uintptr_t)data & 31) == 0);
    assert(vertrix_sequence_player_pcm(reference, 64, 1, scratch, 128, expected, 256));
    assert(!memcmp(expected, data, 256));
    submitted++;
}
void DCFlushRange(void *data, uint32_t bytes)
{
    assert(data && !((uintptr_t)data & 31) && bytes == 256);
    flushed++;
}
s32 ASND_SetVoice(s32 voice, s32 format, s32 pitch, s32 delay, void *data, s32 bytes, s32 left,
                  s32 right, void (*callback)(s32))
{
    assert(voice == 2 && format == 7 && pitch == 48000 && !delay && left == 255 && right == 255 &&
           callback);
    assert(!active && !queued);
    compare(data, bytes);
    active = data;
    handler = callback;
    return SND_OK;
}
s32 ASND_AddVoice(s32 voice, void *data, s32 bytes)
{
    assert(voice == 2 && data != active && data != queued);
    if (busy)
    {
        busy = 0;
        return SND_BUSY;
    }
    if (invalid)
        return SND_INVALID;
    assert(!queued);
    compare(data, bytes);
    queued = data;
    return SND_OK;
}
s32 ASND_StopVoice(s32 voice)
{
    assert(voice == 2);
    active = queued = NULL;
    stopped++;
    return SND_OK;
}
s32 ASND_TestPointer(s32 voice, void *data)
{
    assert(voice == 2);
    return data == active || data == queued;
}
s32 ASND_TestVoiceBufferReady(s32 voice)
{
    assert(voice == 2);
    return queued ? 0 : 1;
}
int main(int argc, char **argv)
{
    assert(argc == 3);
    VertrixVf *vf = vertrix_vf_open(argv[1]);
    assert(vf);
    VertrixSequenceModule *module = vertrix_sequence_module_load(vf, argv[2], 0, NULL);
    assert(module);
    vertrix_vf_close(vf);
    reference = vertrix_sequence_player_create(module, 48000, 255, 1, 1);
    assert(reference);
    assert(!vertrix_wii_music_create(module, 48001, 255, 1, 64));
    assert(!vertrix_wii_music_create(module, 48000, 255, 1, 63));
    assert(!vertrix_wii_music_create(module, 48000, 257, 1, 64));
    VertrixWiiMusic *music = vertrix_wii_music_create(module, 48000, 255, 1, 64);
    assert(music);
    assert(vertrix_wii_music_pump(music) == -1);
    assert(!vertrix_wii_music_start(music, 2, 256, 255));
    busy = 1;
    assert(vertrix_wii_music_start(music, 2, 255, 255));
    assert(submitted == 1 && flushed == 2);
    handler(2);
    assert(submitted == 1 && flushed == 2);
    assert(vertrix_wii_music_pump(music) == 1 && submitted == 2 && flushed == 2);
    assert(!vertrix_wii_music_start(music, 2, 255, 255));
    for (unsigned i = 0; i < 128; i++)
    {
        assert(!vertrix_wii_music_pump(music));
        active = queued;
        queued = NULL;
        unsigned before = flushed;
        busy = 1;
        assert(!vertrix_wii_music_pump(music) && flushed == before + 1);
        assert(vertrix_wii_music_pump(music) == 1 && flushed == before + 1);
    }
    active = queued;
    queued = NULL;
    invalid = 1;
    assert(vertrix_wii_music_pump(music) == -1);
    assert(vertrix_wii_music_pump(music) == -1);
    vertrix_wii_music_free(music);
    assert(stopped == 1 && !active && !queued);
    vertrix_wii_music_free(NULL);
    vertrix_sequence_player_free(reference);
    vertrix_sequence_module_free(module);
    assert(submitted == 130);
    printf("%s: %u buffers passed\n", argv[2], submitted);
}
