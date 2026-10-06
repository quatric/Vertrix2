#include "wii_audio.h"
#include <asndlib.h>
#include <gccore.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

int vertrix_wii_pcm8_load(VertrixVf *archive, const char *name, VertrixWiiPcm8 *output)
{
    if (!output || output->samples || output->allocation || output->playing ||
        output->sample_count || output->sample_rate || output->padded_size)
    {
        return 0;
    }
    VertrixPcm8 decoded = {0};
    if (!vertrix_audio_pcm8(archive, name, &decoded))
    {
        return 0;
    }
    if (decoded.sample_count > INT_MAX - 31 || decoded.sample_rate > MAX_PITCH)
    {
        vertrix_pcm8_free(&decoded);
        return 0;
    }
    uint32_t padded = (decoded.sample_count + 31) & ~31u;
    void *allocation = malloc((size_t)padded + 31);
    if (!allocation)
    {
        vertrix_pcm8_free(&decoded);
        return 0;
    }
    unsigned char *samples = (unsigned char *)(((uintptr_t)allocation + 31) & ~(uintptr_t)31);
    memset(samples, 128, padded);
    memcpy(samples, decoded.samples, decoded.sample_count);
    DCFlushRange(samples, padded);
    *output = (VertrixWiiPcm8){
        samples, allocation, decoded.sample_rate, decoded.sample_count, padded, 0, 0};
    vertrix_pcm8_free(&decoded);
    return 1;
}

void vertrix_wii_pcm8_stop(VertrixWiiPcm8 *audio)
{
    if (audio && audio->playing)
    {
        ASND_StopVoice(audio->voice);
        audio->playing = 0;
    }
}

int vertrix_wii_pcm8_play(VertrixWiiPcm8 *audio, int voice, unsigned left, unsigned right)
{
    if (!audio || !audio->samples || !audio->allocation || !audio->sample_count ||
        !audio->sample_rate || audio->sample_rate > MAX_PITCH || audio->sample_count > INT_MAX ||
        voice < 0 || voice >= MAX_SND_VOICES || left > MAX_VOLUME || right > MAX_VOLUME)
    {
        return 0;
    }
    vertrix_wii_pcm8_stop(audio);
    if (ASND_SetVoice(voice, VOICE_MONO_8BIT_U, (int)audio->sample_rate, 0, audio->samples,
                      (int)audio->sample_count, (int)left, (int)right, NULL) != SND_OK)
    {
        return 0;
    }
    audio->voice = voice;
    audio->playing = 1;
    return 1;
}

void vertrix_wii_pcm8_free(VertrixWiiPcm8 *audio)
{
    if (audio)
    {
        vertrix_wii_pcm8_stop(audio);
        free(audio->allocation);
        memset(audio, 0, sizeof(*audio));
    }
}
