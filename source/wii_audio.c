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

#define STREAM_BLOCK 4096 /* bytes of 16-bit stereo: 1024 frames */
#define STREAM_BLOCKS 48

static uint8_t stream_data[STREAM_BLOCKS][STREAM_BLOCK] __attribute__((aligned(32)));
static uint8_t stream_silence[STREAM_BLOCK] __attribute__((aligned(32)));
static volatile uint32_t stream_read, stream_write;
static uint32_t stream_fill, stream_rate;
static int stream_voice = -1;

/* ASND asks for the next buffer while the current one plays. */
static void stream_next(s32 voice)
{
    if (stream_read != stream_write)
    {
        if (ASND_AddVoice(voice, stream_data[stream_read % STREAM_BLOCKS], STREAM_BLOCK) == SND_OK)
        {
            stream_read++;
        }
    }
    else
    {
        ASND_AddVoice(voice, stream_silence, STREAM_BLOCK);
    }
}

void vertrix_wii_stream_stop(void)
{
    if (stream_voice >= 0)
    {
        ASND_StopVoice(stream_voice);
    }
    stream_voice = -1;
    stream_read = stream_write = 0;
    stream_fill = 0;
}

static void stream_frame(int16_t left, int16_t right)
{
    /* Two blocks stay out of reach: the one ASND plays and the one it has queued. */
    if (stream_write - stream_read >= STREAM_BLOCKS - 2)
    {
        return;
    }
    int16_t *out = (int16_t *)stream_data[stream_write % STREAM_BLOCKS];
    out[stream_fill / 2] = left;
    out[stream_fill / 2 + 1] = right;
    stream_fill += 4;
    if (stream_fill == STREAM_BLOCK)
    {
        DCFlushRange(out, STREAM_BLOCK);
        stream_fill = 0;
        stream_write++;
    }
}

void vertrix_wii_stream_write(int voice, const uint8_t *samples, uint32_t bytes, uint32_t rate,
                              uint32_t channels, uint32_t bits)
{
    if (samples == NULL || rate == 0 || rate > MAX_PITCH || (channels != 1 && channels != 2) ||
        (bits != 8 && bits != 16) || voice < 0 || voice >= MAX_SND_VOICES)
    {
        return;
    }
    if (voice != stream_voice || rate != stream_rate)
    {
        vertrix_wii_stream_stop();
        DCFlushRange(stream_silence, STREAM_BLOCK);
        if (ASND_SetVoice(voice, VOICE_STEREO_16BIT, (int)rate, 0, stream_silence, STREAM_BLOCK,
                          MAX_VOLUME, MAX_VOLUME, stream_next) != SND_OK)
        {
            return;
        }
        stream_voice = voice;
        stream_rate = rate;
    }
    uint32_t frame = channels * (bits / 8);
    for (uint32_t at = 0; at + frame <= bytes; at += frame)
    {
        const uint8_t *in = samples + at;
        int16_t left, right;
        if (bits == 8)
        {
            left = (int16_t)((in[0] - 128) << 8);
            right = channels == 2 ? (int16_t)((in[1] - 128) << 8) : left;
        }
        else
        {
            left = (int16_t)(in[0] | in[1] << 8);
            right = channels == 2 ? (int16_t)(in[2] | in[3] << 8) : left;
        }
        stream_frame(left, right);
    }
}
