/* Decode every Vertrix 3 texture of vertrix3.vf with the shared loaders (source/png.c for PNG,
 * source/image.c for PCX) and every WAV effect (source/audio.c, 8- or 16-bit) and print name, size
 * and an FNV-1a hash of the result, for tools/v3_assets_check.py to compare with an independent
 * decoder.
 *
 * usage: v3_assets_check VERTRIX3_VF */
#include <stdio.h>
#include <string.h>
#include <strings.h>

#include "audio.h"
#include "image.h"
#include "png.h"
#include "vf.h"

static unsigned long long fnv(const unsigned char *data, size_t size, unsigned long long hash)
{
    for (size_t i = 0; i < size; ++i)
    {
        hash = (hash ^ data[i]) * 1099511628211ULL;
    }
    return hash;
}

static int ends_with(const char *name, const char *suffix)
{
    const size_t a = strlen(name);
    const size_t b = strlen(suffix);
    return a >= b && strcasecmp(name + a - b, suffix) == 0;
}

int main(int argc, char **argv)
{
    VertrixVf *archive = argc > 1 ? vertrix_vf_open(argv[1]) : NULL;
    if (!archive)
    {
        fprintf(stderr, "usage: v3_assets_check VERTRIX3_VF\n");
        return 2;
    }
    unsigned failed = 0;
    for (uint32_t i = 0; i < vertrix_vf_count(archive); ++i)
    {
        const char *name = vertrix_vf_name(archive, i);
        if (ends_with(name, ".png"))
        {
            VertrixImage image = {0};
            if (!vertrix_image_png(archive, name, &image))
            {
                printf("%s\tFAILED\n", name);
                ++failed;
                continue;
            }
            printf("%s\t%ux%u\t%016llx\n", name, image.width, image.height,
                   fnv(image.rgba, (size_t)image.width * image.height * 4, 1469598103934665603ULL));
            vertrix_image_free(&image);
        }
        else if (ends_with(name, ".wav"))
        {
            VertrixPcm8 pcm8 = {0};
            VertrixPcm16 pcm16 = {0};
            if (vertrix_audio_pcm8(archive, name, &pcm8))
            {
                printf("%s\t8@%u\t%016llx\n", name, pcm8.sample_rate,
                       fnv(pcm8.samples, pcm8.sample_count, 1469598103934665603ULL));
                vertrix_pcm8_free(&pcm8);
            }
            else if (vertrix_audio_pcm16(archive, name, &pcm16))
            {
                /* Hashed as little-endian bytes, whatever the host order. */
                unsigned long long hash = 1469598103934665603ULL;
                for (uint32_t s = 0; s < pcm16.sample_count; ++s)
                {
                    const unsigned char bytes[2] = {
                        (unsigned char)(pcm16.samples[s] & 0xff),
                        (unsigned char)((uint16_t)pcm16.samples[s] >> 8)};
                    hash = fnv(bytes, 2, hash);
                }
                printf("%s\t16@%u\t%016llx\n", name, pcm16.sample_rate, hash);
                vertrix_pcm16_free(&pcm16);
            }
            else
            {
                printf("%s\tFAILED\n", name);
                ++failed;
            }
        }
        else if (ends_with(name, ".pcx"))
        {
            VertrixPcx image = {0};
            if (!vertrix_image_pcx(archive, name, &image))
            {
                printf("%s\tFAILED\n", name);
                ++failed;
                continue;
            }
            unsigned long long hash =
                fnv(image.indices, (size_t)image.width * image.height, 1469598103934665603ULL);
            printf("%s\t%ux%u\t%016llx\n", name, image.width, image.height,
                   fnv(image.palette, sizeof image.palette, hash));
            vertrix_pcx_free(&image);
        }
    }
    vertrix_vf_close(archive);
    return failed != 0;
}
