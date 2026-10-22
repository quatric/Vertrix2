#!/usr/bin/env python3
"""A Mac app icon (.icns) from a game's own icon.

    icon.py SOURCE OUT.icns

SOURCE is a Windows executable, whose icon group's images are used (each size of the .icns from
the largest image that is not larger, scaled up by whole pixels), or a PNG (8-bit RGB or RGBA,
not interlaced), centred on a square. Needs pefile for an executable and iconutil (macOS)."""
import os
import shutil
import struct
import sys
import tempfile
import zlib

def png_write(path, width, height, rgba):
    rows = b''.join(b'\0' + bytes(rgba[y * width * 4:(y + 1) * width * 4]) for y in range(height))

    def chunk(kind, data):
        return (struct.pack('>I', len(data)) + kind + data +
                struct.pack('>I', zlib.crc32(kind + data) & 0xffffffff))

    with open(path, 'wb') as f:
        f.write(b'\x89PNG\r\n\x1a\n')
        f.write(chunk(b'IHDR', struct.pack('>IIBBBBB', width, height, 8, 6, 0, 0, 0)))
        f.write(chunk(b'IDAT', zlib.compress(rows, 9)))
        f.write(chunk(b'IEND', b''))


def png_read(path):
    data = open(path, 'rb').read()
    pos, idat = 8, b''
    while pos < len(data):
        length, kind = struct.unpack('>I4s', data[pos:pos + 8])
        body = data[pos + 8:pos + 8 + length]
        if kind == b'IHDR':
            width, height, depth, colour, _, _, interlace = struct.unpack('>IIBBBBB', body)
            if depth != 8 or colour not in (2, 6) or interlace:
                sys.exit('%s: only 8-bit RGB or RGBA PNGs' % path)
        elif kind == b'IDAT':
            idat += body
        pos += 12 + length
    channels = 4 if colour == 6 else 3
    raw = zlib.decompress(idat)
    stride = width * channels
    out, previous = bytearray(), bytearray(stride)
    for y in range(height):
        kind = raw[y * (stride + 1)]
        line = bytearray(raw[y * (stride + 1) + 1:(y + 1) * (stride + 1)])
        for i in range(stride):
            a = line[i - channels] if i >= channels else 0
            b = previous[i]
            c = previous[i - channels] if i >= channels else 0
            if kind == 1:
                line[i] = (line[i] + a) & 255
            elif kind == 2:
                line[i] = (line[i] + b) & 255
            elif kind == 3:
                line[i] = (line[i] + (a + b) // 2) & 255
            elif kind == 4:
                p = a + b - c
                pa, pb, pc = abs(p - a), abs(p - b), abs(p - c)
                line[i] = (line[i] + (a if pa <= pb and pa <= pc else b if pb <= pc else c)) & 255
        previous = line
        for x in range(width):
            px = line[x * channels:(x + 1) * channels]
            out += px if channels == 4 else px + b'\xff'
    return width, height, out


def dib_read(dib):
    """An icon image (a DIB with its AND mask) as (width, height, RGBA rows from the top)."""
    if dib[:8] == b'\x89PNG\r\n\x1a\n':
        with tempfile.NamedTemporaryFile(suffix='.png') as f:
            f.write(dib)
            f.flush()
            return png_read(f.name)
    size, width, height2, _, bits = struct.unpack('<IiiHH', dib[:16])
    height = height2 // 2
    colours = struct.unpack('<I', dib[32:36])[0] or (1 << bits if bits <= 8 else 0)
    palette = dib[size:size + 4 * colours]
    pixels = size + 4 * colours
    stride = (width * bits + 31) // 32 * 4
    mask_at = pixels + stride * height
    mask_stride = (width + 31) // 32 * 4
    out = bytearray()
    has_alpha = bits == 32 and any(
        dib[pixels + i * 4 + 3] for i in range(width * height))
    for y in range(height):
        row = pixels + (height - 1 - y) * stride
        mask_row = mask_at + (height - 1 - y) * mask_stride
        for x in range(width):
            if bits == 32:
                b, g, r, a = dib[row + 4 * x:row + 4 * x + 4]
            elif bits == 24:
                b, g, r = dib[row + 3 * x:row + 3 * x + 3]
                a = 255
            else:
                index = (dib[row + x * bits // 8] >> (8 - bits - (x * bits) % 8)) & ((1 << bits) - 1)
                b, g, r = palette[4 * index:4 * index + 3]
                a = 255
            if not has_alpha:
                masked = dib[mask_row + x // 8] >> (7 - x % 8) & 1
                a = 0 if masked else 255
            out += bytes((r, g, b, a))
    return width, height, out


def exe_images(path):
    import pefile
    pe = pefile.PE(path)
    icons, groups = {}, []
    for kind in pe.DIRECTORY_ENTRY_RESOURCE.entries:
        for entry in kind.directory.entries:
            for language in entry.directory.entries:
                data = pe.get_data(language.data.struct.OffsetToData, language.data.struct.Size)
                if kind.struct.Id == 3:
                    icons[entry.id] = data
                elif kind.struct.Id == 14:
                    groups.append(data)
    if not groups:
        sys.exit('%s has no icon' % path)
    group = groups[0]
    count = struct.unpack('<H', group[4:6])[0]
    images = []
    for i in range(count):
        bits, = struct.unpack('<H', group[6 + 14 * i + 6:6 + 14 * i + 8])
        ident, = struct.unpack('<H', group[6 + 14 * i + 12:6 + 14 * i + 14])
        if ident in icons:
            width, height, rgba = dib_read(icons[ident])
            images.append((width, bits, width, height, rgba))
    return [(w, h, rgba) for _, _, w, h, rgba in sorted(images, key=lambda i: (i[0], i[1]))]


def square(image, size):
    """The image scaled by whole pixels (or down, to fit) and centred on a size x size square."""
    width, height, rgba = image
    scale = max(1, size // max(width, height))
    shrink = max(width, height) > size
    w = size * width // max(width, height) if shrink else width * scale
    h = size * height // max(width, height) if shrink else height * scale
    out = bytearray(size * size * 4)
    left, top = (size - w) // 2, (size - h) // 2
    for y in range(h):
        sy = y * height // h
        for x in range(w):
            sx = x * width // w
            at = 4 * ((top + y) * size + left + x)
            out[at:at + 4] = rgba[4 * (sy * width + sx):4 * (sy * width + sx) + 4]
    return out


def main():
    source, target = sys.argv[1], sys.argv[2]
    images = [png_read(source)] if source.lower().endswith('.png') else exe_images(source)
    folder = tempfile.mkdtemp(suffix='.iconset')
    try:
        for points in (16, 32, 128, 256, 512):
            for name, size in (('icon_%dx%d.png' % (points, points), points),
                               ('icon_%dx%d@2x.png' % (points, points), 2 * points)):
                fitting = [i for i in images if max(i[0], i[1]) <= size]
                image = fitting[-1] if fitting else images[0]
                png_write(os.path.join(folder, name), size, size, square(image, size))
        if os.system('iconutil -c icns "%s" -o "%s"' % (folder, target)) != 0:
            sys.exit('iconutil failed')
    finally:
        shutil.rmtree(folder)


if __name__ == '__main__':
    main()
