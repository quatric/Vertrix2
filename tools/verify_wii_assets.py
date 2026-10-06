""
    "Host integration check; GX calls are recorded stubs, never GPU validation."
    "" import argparse import json import subprocess from pathlib import Path

        HEADER = r ""
                   "
#ifndef TEST_GCCORE_H
#define TEST_GCCORE_H
#include <stdint.h>
    typedef struct
{
    void *data;
    uint16_t width, height;
    uint8_t min, mag;
} GXTexObj;
#define GX_NEAR 0
#define GX_LINEAR 1
#define GX_TF_RGBA8 6
#define GX_CLAMP 0
#define GX_FALSE 0
#define GX_TEXMAP7 7
extern unsigned flushes, finishes;
void DCFlushRange(void *, uint32_t);
void GX_InvalidateTexAll(void);
void GX_InitTexObj(GXTexObj *, void *, uint16_t, uint16_t, uint8_t, uint8_t, uint8_t, uint8_t);
void GX_InitTexObjFilterMode(GXTexObj *, uint8_t, uint8_t);
void GX_LoadTexObj(GXTexObj *, uint32_t);
void GX_DrawDone(void);
#endif
""
    "
    HARNESS = r ""
                "
#include "wii_assets.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
    unsigned flushes,
    finishes;
void DCFlushRange(void *data, uint32_t size)
{
    assert(data && size && !(size % 64));
    ++flushes;
}
void GX_InvalidateTexAll(void)
{
}
void GX_InitTexObj(GXTexObj *o, void *p, uint16_t w, uint16_t h, uint8_t f, uint8_t s, uint8_t t,
                   uint8_t m)
{
    assert(f == GX_TF_RGBA8 && s == GX_CLAMP && t == GX_CLAMP && !m);
    o->data = p;
    o->width = w;
    o->height = h;
}
void GX_InitTexObjFilterMode(GXTexObj *o, uint8_t min, uint8_t mag)
{
    o->min = min;
    o->mag = mag;
}
void GX_LoadTexObj(GXTexObj *o, uint32_t map)
{
    assert(o->data && map <= 7);
}
void GX_DrawDone(void)
{
    ++finishes;
}
int main(int argc, char **argv)
{
    assert(argc == 2);
    VertrixVf *vf = vertrix_vf_open(argv[1]);
    assert(vf);
    const uint32_t masks[3] = {0xff0000, 0xff00, 0xff};
    unsigned pixels = 0;
    for (unsigned character = 0; character < 18; ++character)
    {
        VertrixWiiBlockSet set = {0};
        VertrixBlockSet reference = {0};
        unsigned filter = character % 2;
        assert(vertrix_wii_block_set_load(vf, character, filter, &set));
        assert(vertrix_asset_block_set(vf, character, masks, &reference));
        assert(set.ready && !memcmp(set.delays, reference.delays, sizeof(set.delays)));
        VertrixWiiBlockSet saved = set;
        assert(!vertrix_wii_block_set_load(vf, character, filter, &set));
        assert(!memcmp(&saved, &set, sizeof(set)));
        for (unsigned color = 0; color < 7; ++color)
            for (unsigned frame = 0; frame < 8; ++frame)
            {
                VertrixWiiTexture *t = &set.frames[color][frame];
                assert(t->ready && t->object.data == t->pixels.data && t->object.width == 24 &&
                       t->object.height == 24);
                assert(t->object.min == filter && t->object.mag == filter && t->u_limit == 1 &&
                       t->v_limit == 1);
                assert(!((uintptr_t)t->pixels.data % 32));
                for (unsigned y = 0; y < 24; ++y)
                    for (unsigned x = 0; x < 24; ++x)
                    {
                        unsigned pair = ((y / 4) * 6 + x / 4) * 64 + ((y % 4) * 4 + x % 4) * 2;
                        const unsigned char *rgba =
                            reference.frames[color][frame].rgba + (y * 24 + x) * 4;
                        const unsigned char *data = t->pixels.data;
                        assert(data[pair] == rgba[3] && data[pair + 1] == rgba[0] &&
                               data[pair + 32] == rgba[1] && data[pair + 33] == rgba[2]);
                        ++pixels;
                    }
                assert(vertrix_wii_texture_bind(t, 0));
            }
        vertrix_block_set_free(&reference);
        vertrix_wii_block_set_free(&set);
        VertrixWiiBlockSet empty = {0};
        assert(!memcmp(&set, &empty, sizeof(set)));
        vertrix_wii_block_set_free(&set);
    }
    for (unsigned character = 18; character < 21; ++character)
    {
        VertrixWiiBlockSet set = {0}, empty = {0};
        assert(!vertrix_wii_block_set_load(vf, character, GX_NEAR, &set));
        assert(!memcmp(&set, &empty, sizeof(set)));
    }
    unsigned sprite_frames = 0, sprite_files = 0, sprite_pixels = 0;
    for (unsigned index = 0; index < vertrix_vf_count(vf); ++index)
    {
        const char *name = vertrix_vf_name(vf, index);
        size_t length = strlen(name);
        if (length < 4 || strcmp(name + length - 4, ".spr"))
            continue;
        ++sprite_files;
        unsigned count = 1;
        for (unsigned frame = 0; frame < count; ++frame)
        {
            VertrixWiiSpriteFrame loaded = {0};
            VertrixSpriteFrame decoded = {0};
            assert(vertrix_wii_sprite_frame_load(vf, name, frame, GX_NEAR, &loaded));
            assert(vertrix_image_sprite_processed(vf, name, frame, masks, &decoded));
            count = decoded.frame_count;
            assert(loaded.frame_count == count &&
                   !memcmp(loaded.metadata, decoded.metadata, sizeof(loaded.metadata)));
            unsigned sw = loaded.texture.pixels.storage_width,
                     sh = loaded.texture.pixels.storage_height;
            for (unsigned y = 0; y < sh; ++y)
                for (unsigned x = 0; x < sw; ++x)
                {
                    unsigned pair = ((y / 4) * (sw / 4) + x / 4) * 64 + ((y % 4) * 4 + x % 4) * 2;
                    const unsigned char *data = loaded.texture.pixels.data;
                    unsigned char zero[4] = {0};
                    const unsigned char *rgba =
                        (x < decoded.image.width && y < decoded.image.height)
                            ? decoded.image.rgba + (y * decoded.image.width + x) * 4
                            : zero;
                    assert(data[pair] == rgba[3] && data[pair + 1] == rgba[0] &&
                           data[pair + 32] == rgba[1] && data[pair + 33] == rgba[2]);
                    ++sprite_pixels;
                }
            VertrixWiiSpriteFrame saved = loaded;
            assert(!vertrix_wii_sprite_frame_load(vf, name, frame, GX_NEAR, &loaded));
            assert(!memcmp(&loaded, &saved, sizeof(loaded)));
            vertrix_sprite_free(&decoded);
            vertrix_wii_sprite_frame_free(&loaded);
            VertrixWiiSpriteFrame empty = {0};
            assert(!memcmp(&loaded, &empty, sizeof(loaded)));
            assert(!vertrix_wii_sprite_frame_load(vf, name, count, GX_NEAR, &loaded));
            assert(!memcmp(&loaded, &empty, sizeof(loaded)));
            ++sprite_frames;
        }
    }
    assert(sprite_files == 20 && sprite_frames == 216);
    assert(flushes == 1224 && finishes == 1224);
    printf("Verified %u SPR files, %u SPR frames and %u padded sprite pixels\n", sprite_files,
           sprite_frames, sprite_pixels);
    vertrix_vf_close(vf);
    printf("Verified %u integrated pixels, %u texture uploads and cleanup calls\n", pixels,
           flushes);
}
"""

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("archive", type=Path)
    parser.add_argument("--build-dir", type=Path, required=True)
    args = parser.parse_args()
    build = args.build_dir.resolve()
    build.mkdir(parents=True, exist_ok=True)
    (build / "gccore.h").write_text(HEADER)
    (build / "harness.c").write_text(HARNESS)
    source = Path(__file__).resolve().parents[1] / "source"
    subprocess.run(["cc", "-std=c11", "-Wall", "-Wextra", "-Werror", "-fsanitize=address,undefined",
                    "-I"+str(build), "-I"+str(source), str(build/"harness.c"),
                    *[str(source/name) for name in ("wii_assets.c", "wii_texture.c", "texture.c", "assets.c", "image.c", "vf.c")],
                    "-o", str(build/"verify-wii-assets")], check=True)
    subprocess.run([str(build/"verify-wii-assets"), str(args.archive.resolve())], check=True)
    (build/"wii-assets-verification.json").write_text(json.dumps({"status":"passed", "characters":18,
        "block_frames":1008,"block_pixels":580608,"sprite_files":20,"sprite_frames":216,"missing_or_invalid_character_rows":3,
        "scope":"Actual VF decoding and Wii asset/texture ownership code under ASan/UBSan. GX/cache calls are host stubs; no GPU or hardware validation."},indent=2)+"\n")

if __name__ == "__main__":
    main()
