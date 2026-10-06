""
    "Verify real Wii PCM ownership code with recorded ASND/cache stubs."
    "" import argparse import json import subprocess from pathlib import Path

        ASND = r ""
                 "
#ifndef TEST_ASND
#define TEST_ASND
#define MAX_PITCH 144000
#define MAX_SND_VOICES 16
#define MAX_VOLUME 255
#define VOICE_MONO_8BIT_U 4
#define SND_OK 0
    int ASND_StopVoice(int voice);
int ASND_SetVoice(int voice, int format, int pitch, int delay, void *data, int size, int left,
                  int right, void (*callback)(int));
#endif
""
    "
    GX = "#include <stdint.h>\nvoid DCFlushRange(void *data,uint32_t size);\n" HARNESS = r ""
                                                                                           "
#include "wii_audio.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
    static unsigned flushes,
    plays, stops;
static int fail_next, active_voice = -1;
static VertrixWiiPcm8 *expected;
void DCFlushRange(void *data, uint32_t size)
{
    assert(data && !((uintptr_t)data % 32) && !(size % 32));
    ++flushes;
}
int ASND_StopVoice(int voice)
{
    assert(voice == active_voice);
    assert(expected && expected->samples);
    active_voice = -1;
    ++stops;
    return 0;
}
int ASND_SetVoice(int voice, int format, int pitch, int delay, void *data, int size, int left,
                  int right, void (*callback)(int))
{
    assert(expected && data == expected->samples && pitch == (int)expected->sample_rate);
    assert(format == 4 && delay == 0 && size == (int)expected->sample_count && left == 123 &&
           right == 234 && !callback);
    assert(active_voice == -1);
    ++plays;
    if (fail_next)
    {
        fail_next = 0;
        return -1;
    }
    active_voice = voice;
    return 0;
}
int main(int argc, char **argv)
{
    assert(argc == 2);
    VertrixVf *vf = vertrix_vf_open(argv[1]);
    assert(vf);
    unsigned files = 0, samples = 0, padding = 0;
    for (unsigned index = 0; index < vertrix_vf_count(vf); ++index)
    {
        const char *name = vertrix_vf_name(vf, index);
        size_t length = strlen(name);
        if (length < 4 || strcmp(name + length - 4, ".wav"))
            continue;
        VertrixWiiPcm8 sound = {0};
        VertrixPcm8 reference = {0};
        assert(vertrix_wii_pcm8_load(vf, name, &sound));
        assert(vertrix_audio_pcm8(vf, name, &reference));
        assert(sound.sample_rate == reference.sample_rate &&
               sound.sample_count == reference.sample_count);
        assert(!memcmp(sound.samples, reference.samples, sound.sample_count));
        assert(sound.padded_size == (sound.sample_count + 31) / 32 * 32);
        for (unsigned i = sound.sample_count; i < sound.padded_size; ++i)
        {
            assert(sound.samples[i] == 128);
            ++padding;
        }
        VertrixWiiPcm8 saved = sound;
        assert(!vertrix_wii_pcm8_load(vf, name, &sound));
        assert(!memcmp(&saved, &sound, sizeof(sound)));
        expected = &sound;
        assert(vertrix_wii_pcm8_play(&sound, 1, 123, 234));
        assert(sound.playing && sound.voice == 1);
        saved = sound;
        assert(!vertrix_wii_pcm8_play(&sound, -1, 123, 234));
        assert(!vertrix_wii_pcm8_play(&sound, 16, 123, 234));
        assert(!vertrix_wii_pcm8_play(&sound, 1, 256, 234));
        assert(!vertrix_wii_pcm8_play(&sound, 1, 123, 256));
        assert(!memcmp(&saved, &sound, sizeof(sound)));
        assert(vertrix_wii_pcm8_play(&sound, 2, 123, 234));
        assert(sound.voice == 2 && sound.playing);
        fail_next = 1;
        assert(!vertrix_wii_pcm8_play(&sound, 3, 123, 234));
        assert(!sound.playing && active_voice == -1);
        assert(vertrix_wii_pcm8_play(&sound, 4, 123, 234));
        samples += sound.sample_count;
        ++files;
        vertrix_wii_pcm8_free(&sound);
        assert(active_voice == -1);
        VertrixWiiPcm8 empty = {0};
        assert(!memcmp(&sound, &empty, sizeof(sound)));
        vertrix_wii_pcm8_free(&sound);
        vertrix_wii_pcm8_stop(&sound);
        assert(!vertrix_wii_pcm8_play(&sound, 1, 123, 234));
        vertrix_pcm8_free(&reference);
    }
    assert(files == 13 && samples == 149076 && flushes == 13 && plays == 52 && stops == 39);
    vertrix_vf_close(vf);
    printf("Verified %u WAV effects, %u samples, %u silent padding bytes, %u ASND submissions and "
           "%u stops\n",
           files, samples, padding, plays, stops);
}
""
    "

    def
    main()
    : parser = argparse.ArgumentParser(description = __doc__) parser
                   .add_argument("archive", type = Path) parser.add_argument(
                       "--build-dir", type = Path, required = True) args = parser.parse_args();
build = args.build_dir.resolve();
build.mkdir(parents = True, exist_ok = True)(build / "asndlib.h").write_text(ASND);
(build / "gccore.h").write_text(GX);(build/"harness.c").write_text(HARNESS)
    source=Path(__file__).resolve().parents[1]/"source"
    subprocess.run(["cc","-std=c11","-Wall","-Wextra","-Werror","-fsanitize=address,undefined",
                    "-I"+str(build),"-I"+str(source),str(build/"harness.c"),
                    *[str(source/name) for name in ("wii_audio.c","audio.c","vf.c")],"-o",str(build/"verify-wii-audio")],check=True)
    subprocess.run([str(build/"verify-wii-audio"),str(args.archive.resolve())],check=True)
    report={"status":"passed","wav_effects":13,"samples":149076,"asnd_submissions":52,"stop_calls":39,
            "scope":"Real VF/WAV/Wii ownership code under ASan/UBSan; ASND/cache calls are recorded host stubs, no audible or DSP validation."}
    (build/"wii-audio-verification.json").write_text(json.dumps(report,indent=2)+"\n")

if __name__=="__main__":main()
