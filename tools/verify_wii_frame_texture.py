"""Verify bounded frame packing and recorded Wii upload synchronization."""
import argparse
import ctypes as c
import itertools
import json
from pathlib import Path
import random
import subprocess

from verify_render_rectangle import Surface
from verify_wii_assets import HEADER


class Texture(c.Structure):
    _fields_ = [
        ('width', c.c_uint32), ('height', c.c_uint32), ('sw', c.c_uint32), ('sh', c.c_uint32),
        ('size', c.c_size_t), ('data', c.c_void_p), ('allocation', c.c_void_p)
    ]


class Object(c.Structure):
    _fields_ = [
        ('data', c.c_void_p), ('width', c.c_uint16), ('height', c.c_uint16),
        ('min', c.c_uint8), ('mag', c.c_uint8)
    ]


class WiiTexture(c.Structure):
    _fields_ = [
        ('pixels', Texture), ('object', Object), ('u', c.c_float), ('v', c.c_float),
        ('ready', c.c_uint)
    ]


STUBS = r'''
#include <assert.h>
#include <gccore.h>
#include <stddef.h>
unsigned flushes, finishes, events[64], event_count;
static unsigned char *watch;
static size_t watch_size;
static unsigned watch_sum;
static unsigned checksum(void)
{
    unsigned value = 0;
    for (size_t i = 0; i < watch_size; ++i)
        value = value * 33 + watch[i];
    return value;
}
void reset_events(void)
{
    event_count = 0;
    watch = NULL;
    watch_size = 0;
}
void set_watch(void *data, size_t size)
{
    watch = data;
    watch_size = size;
    watch_sum = checksum();
}
static void record(unsigned event)
{
    assert(event_count < 64);
    events[event_count++] = event;
}
void DCFlushRange(void *data, uint32_t size)
{
    assert(data && !((size_t)data & 31) && size && !(size % 64));
    ++flushes;
    record(1);
}
void GX_InvalidateTexAll(void)
{
    record(2);
}
void GX_InitTexObj(GXTexObj *o, void *p, uint16_t w, uint16_t h, uint8_t f, uint8_t s, uint8_t t,
                   uint8_t m)
{
    assert(f == GX_TF_RGBA8 && s == GX_CLAMP && t == GX_CLAMP && !m);
    o->data = p;
    o->width = w;
    o->height = h;
    record(3);
}
void GX_InitTexObjFilterMode(GXTexObj *o, uint8_t min, uint8_t mag)
{
    o->min = min;
    o->mag = mag;
    record(4);
}
void GX_LoadTexObj(GXTexObj *o, uint32_t map)
{
    assert(o->data && map <= 7);
    record(6);
}
void GX_DrawDone(void)
{
    if (watch)
        assert(checksum() == watch_sum);
    ++finishes;
    record(5);
}
'''


def check_pixels(texture, source, stride, slots):
    data = c.string_at(texture.data, texture.size)
    for y in range(texture.sh):
        for x in range(texture.sw):
            offset = ((y // 4) * (texture.sw // 4) + x // 4) * 64 + ((y % 4) * 4 + x % 4) * 2
            actual = (data[offset + 1], data[offset + 32], data[offset + 33], data[offset])
            expected = tuple(source[y * stride + x * 4 + slot] for slot in slots) if (
                y < texture.height and x < texture.width) else (0, 0, 0, 0)
            assert actual == expected, (x, y, actual, expected)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    build = args.build_dir.resolve()
    build.mkdir(parents=True, exist_ok=True)
    root = Path(__file__).resolve().parents[1]
    (build / 'gccore.h').write_text(HEADER)
    (build / 'stubs.c').write_text(STUBS)
    library = build / 'wii-frame-texture.dylib'
    subprocess.run(['cc', '-shared', '-fPIC', '-O2', '-Wall', '-Wextra', '-Werror',
        '-I', str(build), '-I', str(root / 'source'), str(build / 'stubs.c'),
        *[str(root / 'source' / name) for name in ('frame_texture.c', 'texture.c',
            'wii_frame_texture.c', 'wii_texture.c')], '-o', str(library)], check=True)
    native = c.CDLL(str(library))
    native.vertrix_wii_frame_texture_init.argtypes = [c.POINTER(Surface), c.POINTER(c.c_uint32),
        c.c_uint8, c.POINTER(WiiTexture)]
    native.vertrix_wii_frame_texture_update.argtypes = [c.POINTER(Surface), c.POINTER(c.c_uint32),
        c.POINTER(WiiTexture)]
    native.vertrix_wii_texture_bind.argtypes = [c.POINTER(WiiTexture), c.c_uint32]
    native.vertrix_wii_texture_free.argtypes = [c.POINTER(WiiTexture)]
    native.set_watch.argtypes = [c.c_void_p, c.c_size_t]
    event_count = c.c_uint.in_dll(native, 'event_count')
    events = (c.c_uint * 64).in_dll(native, 'events')
    rng = random.Random(0x475850)
    orders = list(itertools.permutations(range(4)))
    pixels = 0
    for case in range(768):
        width, height = (640, 480) if case == 0 else (rng.randrange(1, 66), rng.randrange(1, 66))
        stride = rng.randrange(width * 4 + 33) if case else width * 4
        size = (height - 1) * stride + width * 4
        data = rng.randbytes(size)
        backing = c.create_string_buffer(data, size)
        frame = Surface(c.addressof(backing), size, width, height, stride, 4)
        slots = orders[case % len(orders)]
        masks = (c.c_uint32 * 3)(*[255 << (slot * 8) for slot in slots[:3]])
        texture = WiiTexture()
        native.reset_events()
        assert native.vertrix_wii_frame_texture_init(c.byref(frame), masks, case % 2, c.byref(texture))
        assert list(events[:event_count.value]) == [1, 2, 3, 4]
        assert texture.ready and not texture.pixels.data % 32
        assert texture.object.data == texture.pixels.data
        assert (texture.object.width, texture.object.height) == (texture.pixels.sw, texture.pixels.sh)
        assert (texture.object.min, texture.object.mag) == (case % 2, case % 2)
        assert abs(texture.u - width / texture.pixels.sw) < 1e-6
        assert abs(texture.v - height / texture.pixels.sh) < 1e-6
        check_pixels(texture.pixels, data, stride, slots)
        before_object = bytes(texture)
        pointer = texture.pixels.data
        native.reset_events()
        native.set_watch(pointer, texture.pixels.size)
        updated = rng.randbytes(size)
        c.memmove(backing, updated, size)
        assert native.vertrix_wii_frame_texture_update(c.byref(frame), masks, c.byref(texture))
        assert list(events[:event_count.value]) == [5, 1, 2]
        assert bytes(texture) == before_object and texture.pixels.data == pointer
        check_pixels(texture.pixels, updated, stride, slots)
        assert bytes(backing) == updated
        before = bytes(texture), c.string_at(pointer, texture.pixels.size)
        native.reset_events()
        frame.size = size - 1
        assert not native.vertrix_wii_frame_texture_update(c.byref(frame), masks, c.byref(texture))
        assert not event_count.value and (bytes(texture), c.string_at(pointer, texture.pixels.size)) == before
        frame.size = size
        bad = (c.c_uint32 * 3)(255, 255, 0xff0000)
        assert not native.vertrix_wii_frame_texture_update(c.byref(frame), bad, c.byref(texture))
        assert not event_count.value and (bytes(texture), c.string_at(pointer, texture.pixels.size)) == before
        assert not native.vertrix_wii_frame_texture_init(c.byref(frame), masks, 0, c.byref(texture))
        assert not event_count.value
        assert native.vertrix_wii_texture_bind(c.byref(texture), case % 8)
        assert list(events[:event_count.value]) == [6]
        native.reset_events()
        native.vertrix_wii_texture_free(c.byref(texture))
        assert list(events[:event_count.value]) == [5, 2]
        assert bytes(texture) == bytes(WiiTexture())
        pixels += width * height
    subprocess.run(['make', '-s', '-C', str(root), 'wii-frames', f'BUILD={build / "powerpc"}'], check=True)
    report = {'status': 'passed', 'frame_upload_cases': 768, 'frame_update_cases': 768,
        'pixels_checked_per_phase': pixels, 'channel_permutations': 24,
        'invalid_backing_preservation_cases': 768, 'invalid_mask_preservation_cases': 768,
        'scope': 'Independent GX tile decoding checks every source/padded channel. Strides include '
                 'overlapping rows; full640x480 included. Recorded GX stubs verify synchronization '
                 'before writes, cache flush/invalidation, retained allocation/object, bind/free. '
                 'Wii upload modules compile against actual libogc for PowerPC. GPU execution, '
                 'final quad/video presentation and full application remain unverified.'}
    (build / 'wii-frame-texture-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
